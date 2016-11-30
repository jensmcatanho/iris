/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016 Jean Michel Catanho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
#include "World.h"
#include "Ambient.h"
#include "LuaState.h"
#include "Object.h"
#include "Ray.h"
#include "Sampler.h"
#include "ShadeRecord.h"
#include "Tracer.h"

void World::Build() {
	std::shared_ptr<LuaState> luaState(new LuaState(shared_from_this()));
	luaState->Start("../Source/Scenes/TestScene3.lua");
	luaState->LoadScene();
}

World::World() :
	m_BackgroundColor(RGBColor::Black),
	m_AmbientPtr(new Ambient),
	m_CameraPtr(nullptr),
	m_TracerPtr(nullptr) {

	m_Pixels = new RGBColor[m_ViewPlane.m_Width * m_ViewPlane.m_Height];
}

void World::DisplayPixel(const int row, const int column, const RGBColor &raw_color) const {
	RGBColor mapped_color;
	RGBColor target_color(1.0f, 0.0f, 0.0f); //TODO: Set target color in build member function

	if (m_ViewPlane.m_OutOfGamut)
		mapped_color = ClampToColor(raw_color, target_color);
	else
		mapped_color = MaxToOne(raw_color);
	
	if (m_ViewPlane.m_Gamma != 1.0)
		mapped_color = RGBColor(glm::pow(mapped_color.r, m_ViewPlane.m_InvGamma),
								glm::pow(mapped_color.g, m_ViewPlane.m_InvGamma),
								glm::pow(mapped_color.b, m_ViewPlane.m_InvGamma));

	m_Pixels[row * m_ViewPlane.m_Width + column].r = mapped_color.r;
	m_Pixels[row * m_ViewPlane.m_Width + column].g = mapped_color.g;
	m_Pixels[row * m_ViewPlane.m_Width + column].b = mapped_color.b;
}

ShadeRecord World::HitObjects(const Ray &ray) {
	ShadeRecord sr(*this);
	double t; 			
	double tmin = kHugeValue;
	glm::vec3 normal;
	glm::vec3 local_hit_point;
	int num_objects = m_Objects.size();
	
	for (int i = 0; i < num_objects; i++)
		if (m_Objects[i]->Hit(ray, t, sr) && t < tmin) {
			sr.m_Hit = true;
			tmin = t;

			sr.m_MaterialPtr = m_Objects[i]->GetMaterial();
			sr.m_HitPoint = ray.m_Origin + static_cast<float>(t) * ray.m_Direction;
			sr.m_Color = m_Objects[i]->GetColor();

			normal = sr.m_Normal;
			local_hit_point = sr.m_LocalHitPoint;
		}

	if (sr.m_Hit) {
		sr.m_T = tmin;
		sr.m_Normal = normal;
		sr.m_LocalHitPoint = local_hit_point;
	}

	return sr;
}

RGBColor World::MaxToOne(const RGBColor &raw_color) const {
	float max_value = (float)glm::max(raw_color.r, glm::max(raw_color.g, raw_color.b));
	
	if (max_value > 1.0)
		return raw_color / max_value;
	else
		return raw_color;
}

RGBColor World::ClampToColor(const RGBColor &raw_color, const RGBColor &target_color) const {
	RGBColor clamped_color(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		clamped_color.r = target_color.r;
		clamped_color.g = target_color.g;
		clamped_color.b = target_color.b;
	}
		
	return clamped_color;
}
