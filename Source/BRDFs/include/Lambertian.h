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
#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "BRDF.h"
#include "RGBColor.h"

class Lambertian : public BRDF {
	public:
		Lambertian();

		virtual RGBColor f(const ShadeRecord &, const glm::vec3 &, const glm::vec3 &) const;

		virtual RGBColor rho(const ShadeRecord &, const glm::vec3 &) const;

		// Setters.
		void SetDiffuseReflection(const float);
		void SetDiffuseColor(const RGBColor &);

	private:
		// Diffuse reflection coefficient.
		float m_DiffuseReflection;

		// Diffuse color.
		RGBColor m_DiffuseColor;

};

inline RGBColor Lambertian::f(const ShadeRecord &sr, const glm::vec3 &wi, const glm::vec3 &wo) const {
	return m_DiffuseColor * m_DiffuseReflection * INV_PI;
}

inline RGBColor Lambertian::rho(const ShadeRecord &sr, const glm::vec3 &wo) const {
	return m_DiffuseColor * m_DiffuseReflection;
}

inline void Lambertian::SetDiffuseReflection(const float kdr) {
	m_DiffuseReflection = kdr;
}

inline void Lambertian::SetDiffuseColor(const RGBColor &color) {
	m_DiffuseColor = color;
}

#endif