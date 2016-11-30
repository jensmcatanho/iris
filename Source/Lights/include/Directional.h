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
#ifndef DIRECTIONAL_H
#define DIRECTIONAL_H

#include "Light.h"
#include "RGBColor.h"

class Directional : public Light {
	public:
		Directional();
		Directional(bool);

		// Return a normalized vector that gives the direction from a hit point to the light.
		virtual glm::vec3 GetDirection(ShadeRecord &);
		virtual RGBColor L(ShadeRecord &);

		virtual bool Shadowed(const Ray &, const ShadeRecord &) const;

		// Setters.
		void SetRadiance(const float);
		void SetColor(const RGBColor &);
		void SetDirection(const glm::vec3 &);

	private:
		float m_Radiance;
		RGBColor m_Color;
		glm::vec3 m_Direction;
};

inline void Directional::SetRadiance(const float radiance) {
	m_Radiance = radiance;
}

inline void Directional::SetColor(const RGBColor &color) {
	m_Color = color;
}

inline void Directional::SetDirection(const glm::vec3 &dir) {
	m_Direction = glm::normalize(dir);
}

#endif