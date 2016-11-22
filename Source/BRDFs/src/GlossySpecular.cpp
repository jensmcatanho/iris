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
#include "GlossySpecular.h"
#include "ShadeRecord.h"

GlossySpecular::GlossySpecular() :
	BRDF(),
	m_SpecularReflection(0.0),
	m_SpecularColor(0.0),
	m_SpecularExp(1.0) {

}

GlossySpecular::GlossySpecular(std::shared_ptr<Sampler> sampler_ptr) :
	BRDF(sampler_ptr),
	m_SpecularReflection(0.0),
	m_SpecularColor(0.0),
	m_SpecularExp(1.0) {

}

inline RGBColor GlossySpecular::f(const ShadeRecord &sr, const glm::vec3 &wi, const glm::vec3 &wo) const {
	RGBColor L;

	glm::vec3 r = -wi + (2.0f * glm::dot(sr.m_Normal, wo) * sr.m_Normal);
	float rdotwo = glm::dot(r, wo);

	if (rdotwo > 0.0)
		L = m_SpecularReflection * glm::pow(rdotwo, m_SpecularExp);

	return L;
}