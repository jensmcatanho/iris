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
#ifndef SHADERECORD_H
#define SHADERECORD_H

// TODO: Check if ShadeRecord needs to be a class instead of a struct.

#include "Prerequisites.h"
#include "Ray.h"
#include "RGBColor.h"

class ShadeRecord {
	public:
		ShadeRecord(World &);

		// Check if the ray hit an object.
		bool m_Hit;

		std::shared_ptr<Material> m_MaterialPtr;

		// Hit point in world coordinates.
		glm::vec3 m_HitPoint;

		// ?
		glm::vec3 m_LocalHitPoint;

		// Normal vector on the hit point.
		glm::vec3 m_Normal;

		// Color on the hit point.
		RGBColor m_Color;

		// "For specular highlights".
		Ray m_Ray;

		// Recursion depth.
		int m_Depth;

		// Ray parameter.
		float m_T;

		// "For area lights".
		glm::vec3 m_Direction;

		World &w;  // TODO: Check if this reference to World is necessary.
};

#endif
