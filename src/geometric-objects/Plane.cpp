/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016-2017 Jean Michel Catanho

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
#include "Plane.h"
#include "Ray.h"
#include "Surface.h"

const double Plane::kEpsilon = 0.00001;

Plane::Plane() :
	Object(),
	m_Point(0.0f, 0.0f, 0.0f),
	m_Normal(0.0f, 1.0f, 0.0f) {

}

bool Plane::Hit(const Ray &ray, double &tmin, Surface &sr) const {
	float t;

	if (Intersection(ray, t)) {
		tmin = t;
		sr.m_Normal = m_Normal;
		sr.m_LocalHitPoint = ray.m_Origin + t * ray.m_Direction;

		return true;
	}

	return false;
}

bool Plane::ShadowHit(const Ray &ray, float &tmin) const {
	float t;

	if (Intersection(ray, t)) {
		tmin = t;
		return true;
	}

	return false;
}

bool Plane::Intersection(const Ray &ray, float &t) const {
	if ((t = static_cast<float>(glm::dot(m_Point - ray.m_Origin, m_Normal) / glm::dot(ray.m_Direction, m_Normal))) > kEpsilon)
		return true;

	return false;
}