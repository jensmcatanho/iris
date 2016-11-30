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
#include "Sphere.h"
#include "Ray.h"
#include "ShadeRecord.h"

const double Sphere::kEpsilon = 0.01;

Sphere::Sphere()
	: Object(),
	  m_Center(0.0f, 0.0f, 0.0f),
	  m_Radius(1.0f) {

}

Sphere::Sphere(glm::vec3 c, float r)
	: Object(),
	  m_Center(c),
	  m_Radius(r) {

}

bool Sphere::Hit(const Ray &ray, double &tmin, ShadeRecord &sr) const {
	float t;
	glm::vec3 temp = ray.m_Origin - m_Center;
	double a = glm::dot(ray.m_Direction, ray.m_Direction);
	double b = glm::dot(2.0f * temp, ray.m_Direction);
	double c = glm::dot(temp, temp) - m_Radius * m_Radius;
	double discriminant = b * b - (4 * a * c);

	if (discriminant < 0.0f)
		return false;

	t = (float)((-b - sqrt(discriminant)) / 2 * a);

	if (t > kEpsilon) {
		tmin = t;
		sr.m_Normal = temp + t * ray.m_Direction;
		sr.m_Normal = sr.m_Normal * (1.0f / m_Radius);
		sr.m_HitPoint = ray.m_Origin + ray.m_Direction * t;
		return true;

	}

	t = (float)((-b + sqrt(discriminant)) / 2 * a);

	if (t > kEpsilon) {
		tmin = t;
		sr.m_Normal = temp + t * ray.m_Direction;
		sr.m_Normal = sr.m_Normal * (1.0f / m_Radius);
		sr.m_HitPoint = ray.m_Origin + ray.m_Direction * t;
		return true;

	}

	return false;
}

bool Sphere::ShadowHit(const Ray &ray, float &tmin) const {
	float t;
	glm::vec3 temp = ray.m_Origin - m_Center;
	double a = glm::dot(ray.m_Direction, ray.m_Direction);
	double b = glm::dot(2.0f * temp, ray.m_Direction);
	double c = glm::dot(temp, temp) - m_Radius * m_Radius;
	double discriminant = b * b - (4 * a * c);

	if (discriminant < 0.0f)
		return false;

	t = (float)((-b - sqrt(discriminant)) / 2 * a);

	if (t > kEpsilon)
		return true;

	t = (float)((-b + sqrt(discriminant)) / 2 * a);

	if (t > kEpsilon)
		return true;

	return false;
}