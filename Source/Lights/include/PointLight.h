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
#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"
#include "RGBColor.h"

class PointLight : public Light {
	public:
		PointLight();
		PointLight(bool);

		virtual glm::vec3 GetDirection(ShadeRecord &);
		virtual RGBColor L(ShadeRecord &);

		// Setters.
		void SetRadiance(const float);
		void SetColor(const RGBColor &);
		void SetPosition(const glm::vec3 &);

	private:
		float m_Ls;
		RGBColor m_Color;
		glm::vec3 m_Position;
};

inline void PointLight::SetRadiance(const float radiance) {
	m_Ls = radiance;
}

inline void PointLight::SetColor(const RGBColor &color) {
	m_Color = color;
}

inline void PointLight::SetPosition(const glm::vec3 &pos) {
	m_Position = pos;
}

#endif