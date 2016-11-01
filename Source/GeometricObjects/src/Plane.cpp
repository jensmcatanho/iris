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
#include "Plane.h"
#include "Ray.h"
#include "ShadeRecord.h"

Plane::Plane()
	: Object(),
	  m_Point(0.0f, 0.0f, 0.0f),
	  m_Normal(0.0f, 1.0f, 0.0f) {

}

Plane::Plane(const glm::vec3 &point, const glm::vec3 &normal)
	: Object(),
	  m_Point(point),
	  m_Normal(glm::normalize(normal)) {

}

bool Plane::Hit(const Ray &ray, double &tmin, ShadeRecord &sr) const {
	float t = glm::dot(m_Point - ray.m_Origin, m_Normal) / glm::dot(ray.m_Direction, m_Normal);

	if (t > kEpsilon) {
		tmin = t;
		sr.m_Normal = m_Normal;
		sr.m_HitPoint = ray.m_Origin + t * ray.m_Direction;

		return true;
	}

	return false;
}
