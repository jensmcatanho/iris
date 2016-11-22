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
#ifndef GLOSSYSPECULAR_H
#define GLOSSYSPECULAR_H

#include "BRDF.h"
#include "RGBColor.h"

class GlossySpecular : public BRDF {
	public:
		GlossySpecular();
		GlossySpecular(std::shared_ptr<Sampler>);

		virtual RGBColor f(const ShadeRecord &, const glm::vec3 &, const glm::vec3 &) const;

		// Setters.
		void SetSpecularReflection(const float);
		void SetSpecularColor(const RGBColor &);
		void SetSpecularColor(const float);
		void SetSpecularColor(const float, const float, const float);
		void SetSpecularExponent(const float);

	private:
		// Specular reflection coefficient.
		float m_SpecularReflection;

		// Specular color.
		RGBColor m_SpecularColor;

		// Specular exponent.
		float m_SpecularExp;
};

inline void GlossySpecular::SetSpecularReflection(const float ksr) {
	m_SpecularReflection = ksr;
}

inline void GlossySpecular::SetSpecularColor(const RGBColor &color) {
	m_SpecularColor = color;
}

inline void GlossySpecular::SetSpecularColor(const float color) {
	m_SpecularColor.r = color;
	m_SpecularColor.g = color;
	m_SpecularColor.b = color;
}

inline void GlossySpecular::SetSpecularColor(const float r, const float g, const float b) {
	m_SpecularColor.r = r;
	m_SpecularColor.g = g;
	m_SpecularColor.b = b;
}

inline void GlossySpecular::SetSpecularExponent(const float ksexp) {
	m_SpecularExp = ksexp;
}

#endif