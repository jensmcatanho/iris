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
#include "Directional.h"
#include "LuaState.h"
#include "Matte.h"
#include "MultiJittered.h"
#include "MultipleObjects.h"
#include "Phong.h"
#include "Pinhole.h"
#include "Plane.h"
#include "PointLight.h"
#include "Ray.h"
#include "RayCast.h"
#include "ShadeRecord.h"
#include "Sphere.h"

void World::Build() {
	std::shared_ptr<LuaState> luaState(new LuaState());
	luaState->Start("../Source/Scenes/TestScene.lua");
	luaState->LoadScene(*this);
	
	m_ViewPlane.SetWidth(400);
	m_ViewPlane.SetHeight(400);
	m_ViewPlane.SetPixelSize(0.5);

	std::shared_ptr<MultiJittered> newSampler(new MultiJittered(16));
	m_ViewPlane.SetSampler(newSampler);

	std::shared_ptr<RayCast> newTracer(new RayCast(shared_from_this()));
	m_TracerPtr = newTracer;
	m_BackgroundColor = RGBColor(0.0f, 0.0f, 0.0f);

	std::shared_ptr<Ambient> ambient_ptr(new Ambient);
	m_AmbientPtr = ambient_ptr;

	std::shared_ptr<Pinhole> pinhole_ptr(new Pinhole);
	pinhole_ptr->SetEye(glm::vec3(0.0, 0.0, 500.0));
	pinhole_ptr->LookAt(glm::vec3(-5.0, 0.0, 0.0));
	pinhole_ptr->SetViewPlaneDistance(850.0);
	SetCamera(pinhole_ptr);

	std::shared_ptr<PointLight> light_ptr(new PointLight);
	light_ptr->SetPosition(glm::vec3(100.0, 50.0, 100.0));
	light_ptr->SetRadiance(3.0);
	AddLight(light_ptr);

	std::shared_ptr<Phong> matte_ptr1(new Phong);
	matte_ptr1->SetAmbientReflection(0.25);
	matte_ptr1->SetDiffuseReflection(0.65);
	matte_ptr1->SetDiffuseColor(1.0, 1.0, 0.0);
	matte_ptr1->SetSpecularReflection(0.05);
	std::shared_ptr<Sphere> sphere_ptr(new Sphere);
	sphere_ptr->SetCenter(glm::vec3(10.0, -5.0, 0.0));
	sphere_ptr->SetRadius(27);
	sphere_ptr->SetMaterial(matte_ptr1);
	AddObject(sphere_ptr);

	std::shared_ptr<Matte> matte_ptr2(new Matte);
	matte_ptr2->SetAmbientReflection(0.15);
	matte_ptr2->SetDiffuseReflection(0.85);
	matte_ptr2->SetDiffuseColor(0.71, 0.4, 0.16);
	std::shared_ptr<Sphere> sphere_ptr2(new Sphere);
	sphere_ptr2->SetCenter(glm::vec3(-25.0, 10.0, -35.0));
	sphere_ptr2->SetRadius(27);
	sphere_ptr2->SetMaterial(matte_ptr2);
	AddObject(sphere_ptr2);

	std::shared_ptr<Matte> matte_ptr3(new Matte);
	matte_ptr3->SetAmbientReflection(0.15);
	matte_ptr3->SetDiffuseReflection(0.50);
	matte_ptr3->SetDiffuseColor(0.0, 0.4, 0.2);
	std::shared_ptr<Plane> plane_ptr(new Plane(glm::vec3(0.0f, 0.0f, -50.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	plane_ptr->SetMaterial(matte_ptr3);
	AddObject(plane_ptr);
}

/*
void World::Build() {
	m_ViewPlane.SetWidth(400);
	m_ViewPlane.SetHeight(400);
	m_ViewPlane.SetPixelSize(0.5);

	std::shared_ptr<MultiJittered> newSampler(new MultiJittered(16));
	m_ViewPlane.SetSampler(newSampler);

	std::shared_ptr<RayCast> newTracer(new RayCast(shared_from_this()));
	m_TracerPtr = newTracer;
	m_BackgroundColor = RGBColor(0.0f, 0.0f, 0.0f);

	std::shared_ptr<Ambient> ambient_ptr(new Ambient);
	m_AmbientPtr = ambient_ptr;

	std::shared_ptr<Pinhole> pinhole_ptr(new Pinhole);
	pinhole_ptr->SetEye(glm::vec3(0.0, 0.0, 50.0));
	pinhole_ptr->LookAt(glm::vec3(0.0, 0.0, -1.0));
	pinhole_ptr->SetViewPlaneDistance(50.0);
	SetCamera(pinhole_ptr);

	std::shared_ptr<PointLight> light_ptr(new PointLight);
	light_ptr->SetPosition(glm::vec3(100.0, 50.0, 100.0));
	light_ptr->SetRadiance(3.0);
	AddLight(light_ptr);

	std::shared_ptr<Matte> matte_ptr1(new Matte);
	matte_ptr1->SetAmbientReflection(0.25);
	matte_ptr1->SetDiffuseReflection(1.0);
	matte_ptr1->SetDiffuseColor(1.0, 1.0, 0.0);
	std::shared_ptr<Sphere> sphere_ptr(new Sphere);
	sphere_ptr->SetCenter(glm::vec3(0, 0, 0.0));
	sphere_ptr->SetRadius(35);
	sphere_ptr->SetMaterial(matte_ptr1);
	AddObject(sphere_ptr);
}
*/

/*
void World::Build() {
	m_ViewPlane.SetWidth(400);
	m_ViewPlane.SetHeight(400);

	std::shared_ptr<Pinhole> pinhole_ptr(new Pinhole);
	pinhole_ptr->SetEye(glm::vec3(0.0, 0.0, 60.0));
	pinhole_ptr->LookAt(glm::vec3(0.0, 0.0, -1.0));
	pinhole_ptr->SetViewPlaneDistance(50.0);
	SetCamera(pinhole_ptr);

	std::shared_ptr<MultiJittered> newSampler(new MultiJittered(16));
	m_ViewPlane.SetSampler(newSampler);
	m_ViewPlane.SetPixelSize(1.0);

	std::shared_ptr<RayCast> newTracer(new RayCast(shared_from_this()));
	m_TracerPtr = newTracer;
	m_BackgroundColor = RGBColor(0.0f, 0.0f, 0.0f);

	std::shared_ptr<Ambient> ambient_ptr(new Ambient);
	m_AmbientPtr = ambient_ptr;

	std::shared_ptr<PointLight> light_ptr(new PointLight);
	light_ptr->SetPosition(glm::vec3(100.0, 50.0, 100.0));
	light_ptr->SetRadiance(3.0);
	AddLight(light_ptr);

	std::shared_ptr<Matte> matte_ptr1(new Matte);
	matte_ptr1->SetAmbientReflection(0.25);
	matte_ptr1->SetDiffuseReflection(0.65);
	matte_ptr1->SetDiffuseColor(1.0f, 0.1f, 0.1f);
	std::shared_ptr<Plane> plane_ptr(new Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	plane_ptr->SetColor(1.0f, 0.1f, 0.1f);
	plane_ptr->SetMaterial(matte_ptr1);
	AddObject(plane_ptr);
}
*/

/*
void World::Build() {
	m_ViewPlane.SetWidth(200);
	m_ViewPlane.SetHeight(200);

	std::shared_ptr<Pinhole> pinhole_ptr(new Pinhole);
	pinhole_ptr->SetEye(glm::vec3(0.0, 0.0, 60.0));
	pinhole_ptr->LookAt(glm::vec3(0.0, 0.0, -1.0));
	pinhole_ptr->SetViewPlaneDistance(50.0);
	SetCamera(pinhole_ptr);

	std::shared_ptr<MultiJittered> newSampler(new MultiJittered(16));
	m_ViewPlane.SetSampler(newSampler);
	m_ViewPlane.SetPixelSize(1.0);

	std::shared_ptr<MultipleObjects> newTracer(new MultipleObjects(shared_from_this()));
	m_TracerPtr = newTracer;
	m_BackgroundColor = RGBColor(0.0f, 0.0f, 0.0f);

	std::shared_ptr<Sphere> sphere_ptr(new Sphere);
	sphere_ptr->SetCenter(glm::vec3(0.0f, 0.0f, 0.0f));
	sphere_ptr->SetRadius(50);
	sphere_ptr->SetColor(0, 1, 0);
	AddObject(sphere_ptr);

	// Back
	std::shared_ptr<Plane> plane_ptr(new Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	plane_ptr->SetColor(0.1f, 0.1f, 0.1f);
	AddObject(plane_ptr);

	// Top
	std::shared_ptr<Plane> plane_ptr2(new Plane(glm::vec3(0.0f, 80.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)));
	plane_ptr2->SetColor(1.0f, 1.0f, 1.0f);
	AddObject(plane_ptr2);

	// Bottom
	std::shared_ptr<Plane> plane_ptr3(new Plane(glm::vec3(0.0f, -80.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	plane_ptr3->SetColor(1.0f, 1.0f, 1.0f);
	AddObject(plane_ptr3);

	// Left
	std::shared_ptr<Plane> plane_ptr4(new Plane(glm::vec3(-80.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	plane_ptr4->SetColor(1.0f, 0.0f, 0.0f);
	AddObject(plane_ptr4);

	// Right
	std::shared_ptr<Plane> plane_ptr5(new Plane(glm::vec3(80.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)));
	plane_ptr5->SetColor(0.0f, 0.0f, 1.0f);
	AddObject(plane_ptr5);
}
*/

World::World() :
	m_BackgroundColor(RGBColor::Black),
	m_AmbientPtr(new Ambient),
	m_CameraPtr(nullptr),
	m_TracerPtr(nullptr) {

	m_Pixels = new RGBColor[m_ViewPlane.m_Width * m_ViewPlane.m_Height];
}

void World::RenderScene() const {
	RGBColor pixelColor;
	Ray ray;
	float zw = 100.0f;
	glm::vec2 samplePoint;
	ray.m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);

	for (int r = 0; r < m_ViewPlane.m_Height; r++)
		for (int c = 0; c <= m_ViewPlane.m_Width; c++) {
			pixelColor = RGBColor::Black;

			for (int i = 0; i < m_ViewPlane.m_NumSamples; i++) {
				samplePoint = m_ViewPlane.m_SamplerPtr->SampleUnitSquare();
				ray.m_Origin = glm::vec3(m_ViewPlane.m_PixelSize * (c - 0.5 * m_ViewPlane.m_Width + samplePoint.x),
					                     m_ViewPlane.m_PixelSize * (r - 0.5 * m_ViewPlane.m_Height + samplePoint.y), zw);
				pixelColor += m_TracerPtr->TraceRay(ray);
				
			}
			
			pixelColor /= m_ViewPlane.m_NumSamples;
			DisplayPixel(r, c, pixelColor);
		}
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
