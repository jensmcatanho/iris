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
#include "PointLight.h"
#include "Object.h"
#include "Surface.h"
#include "Scene.h"

PointLight::PointLight() :
	Light(),
	m_Intensity(1.0),
	m_Color(1.0),
	m_Position(0.0),
	m_Attenuate(false),
	m_Decay(2.0) {

}

glm::vec3 PointLight::GetDirection(Surface &sr) {
	return glm::normalize(m_Position - sr.m_HitPoint);
}

RGBColor PointLight::L(Surface &sr) {
	if (m_Attenuate)
		return (m_Color * m_Intensity) / glm::pow(glm::length(m_Position - sr.m_HitPoint), m_Decay);
	else
		return m_Color * m_Intensity;
}

bool PointLight::Shadowed(const Ray &ray, const Surface &sr) const {
	float t;
	int num_objects = sr.w.m_Objects.size();
	float distance = glm::distance(m_Position, ray.m_Origin);

	for (int i = 0; i < num_objects; i++)
		if (sr.w.m_Objects[i]->ShadowHit(ray, t) && t < distance)
			return true;

	return false;
}