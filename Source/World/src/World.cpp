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

#include "MultiJittered.h"
#include "MultipleObjects.h"
#include "Plane.h"
#include "Ray.h"
#include "ShadeRecord.h"
#include "Sphere.h"

void World::Build() {
	m_ViewPlane.SetWidth(200);
	m_ViewPlane.SetHeight(200);
	
	std::shared_ptr<MultiJittered> newSampler(new MultiJittered(256));
	m_ViewPlane.SetSampler(newSampler);
	m_ViewPlane.SetPixelSize(1.0);

	std::shared_ptr<MultipleObjects> newTracer(new MultipleObjects(shared_from_this()));
	m_TracerPtr = newTracer;
	m_BackgroundColor = RGBColor(0.0f, 0.0f, 0.0f);

	std::shared_ptr<Sphere> sphere_ptr(new Sphere);
	sphere_ptr->SetCenter(glm::vec3(0.0f, 0.0f, 0.0f));
	sphere_ptr->SetRadius(80);
	sphere_ptr->SetColor(0, 1, 0);
	AddObject(sphere_ptr);

	// Back
	std::shared_ptr<Plane> plane_ptr(new Plane(glm::vec3(0.0f, 0.0f, -80.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	plane_ptr->SetColor(0.1f, 0.1f, 0.1f);
	AddObject(plane_ptr);

	// Top
	std::shared_ptr<Plane> plane_ptr2(new Plane(glm::vec3(0.0f, 80.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.2f)));
	plane_ptr2->SetColor(1.0f, 1.0f, 1.0f);
	AddObject(plane_ptr2);

	// Bottom
	std::shared_ptr<Plane> plane_ptr3(new Plane(glm::vec3(0.0f, -80.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.2f)));
	plane_ptr3->SetColor(1.0f, 1.0f, 1.0f);
	AddObject(plane_ptr3);

	// Left
	std::shared_ptr<Plane> plane_ptr4(new Plane(glm::vec3(-80.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.2f)));
	plane_ptr4->SetColor(1.0f, 0.0f, 0.0f);
	AddObject(plane_ptr4);

	// Right
	std::shared_ptr<Plane> plane_ptr5(new Plane(glm::vec3(80.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.2f)));
	plane_ptr5->SetColor(0.0f, 0.0f, 1.0f);
	AddObject(plane_ptr5);
}

World::World()
	: m_BackgroundColor(RGBColor::Black),
	  m_TracerPtr(nullptr) {

	m_Pixels = new RGBColor[m_ViewPlane.m_Width * m_ViewPlane.m_Height];
}

World::~World() {
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
			
			pixelColor.r /= m_ViewPlane.m_NumSamples;
			pixelColor.g /= m_ViewPlane.m_NumSamples;
			pixelColor.b /= m_ViewPlane.m_NumSamples;
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
	double tmin = 1000000;
	int num_objects = m_Objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (m_Objects[j]->Hit(ray, t, sr) && (t < tmin)) {
			sr.m_Hit =  true;
			tmin = t;
			sr.m_Color = m_Objects[j]->GetColor();
		}
		
	return (sr);
}

RGBColor World::MaxToOne(const RGBColor &raw_color) const {
	float max_value = (float)glm::max(raw_color.r, glm::max(raw_color.g, raw_color.b));
	
	if (max_value > 1.0)
		return RGBColor(raw_color.r/max_value, raw_color.g/max_value, raw_color.b/max_value);
	else
		return (raw_color);
}

RGBColor World::ClampToColor(const RGBColor &raw_color, const RGBColor &target_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = target_color.r;
		c.g = target_color.g;
		c.b = target_color.b;
	}
		
	return (c);
}
