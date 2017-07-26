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
#include "BlinnPhong.h"
#include "Surface.h"

BlinnPhong::BlinnPhong() :
	BRDF(),
	m_SpecularReflection(0.0),
	m_SpecularColor(0.0),
	m_SpecularExp(1.0) {

}

inline RGBColor BlinnPhong::f(const Surface &sr, const glm::vec3 &wi, const glm::vec3 &wo) const {
	glm::vec3 h = glm::normalize(wi + wo);
	float hdotn = glm::dot(h, sr.m_Normal);

	if (hdotn > 0.0)
		return m_SpecularReflection * glm::pow(hdotn, m_SpecularExp);

	return RGBColor::Black;
}