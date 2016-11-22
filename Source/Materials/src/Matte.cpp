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
#include "Matte.h"
#include "Light.h"
#include "ShadeRecord.h"
#include "World.h"

Matte::Matte() :
	Material(),
	m_Ambient(new Lambertian),
	m_Diffuse(new Lambertian) {

}

RGBColor Matte::Shade(ShadeRecord &sr) const {
	glm::vec3 wo = -sr.m_Ray.m_Direction;
	RGBColor  L = m_Ambient->rho(sr, wo) * sr.w.m_AmbientPtr->L(sr);
	int num_lights = sr.w.m_Lights.size();

	for (int i = 0; i < num_lights; i++) {
		glm::vec3 wi(sr.w.m_Lights[i]->GetDirection(sr));
		float ndotwi = glm::dot(sr.m_Normal, wi);
		float ndotwo = glm::dot(sr.m_Normal, wo);

		if (ndotwi > 0.0 && ndotwo > 0.0)
			L += m_Diffuse->f(sr, wo, wi) * sr.w.m_Lights[i]->L(sr) * ndotwi;
	}

	return L;
}