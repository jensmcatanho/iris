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
#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {
	public:
		// Default constructor.
		Plane();

		// Return true and shading information if a ray intersects with this Object.
		virtual bool Hit(const Ray &, double &, ShadeRecord &) const;

		// Return true if a shadow ray intersects with this Object.
		virtual bool ShadowHit(const Ray &, float &) const;

		void SetPoint(const glm::vec3 &);
		void SetNormal(const glm::vec3 &);
		
	private:
		// Point of the Plane in world coordinates.
		glm::vec3 m_Point;

		// Normal of the Plane normalized.
		glm::vec3 m_Normal;

		// Epsilon factor.
		static const double kEpsilon;
};

inline void Plane::SetPoint(const glm::vec3 &point) {
	m_Point = point;
}

inline void Plane::SetPoint(const glm::vec3 &normal) {
	m_Normal = glm::normalize(normal);
}

#endif
