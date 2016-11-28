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
#ifndef PHONG_H
#define PHONG_H

#include "Material.h"
#include "Lambertian.h"
#include "GlossySpecular.h"

class Phong : public Material {
	public:
		Phong();

		virtual RGBColor Shade(ShadeRecord &) const;

		// Setters.
		void SetAmbientReflection(const float);
		void SetDiffuseReflection(const float);
		void SetDiffuseColor(const RGBColor &);
		void SetDiffuseColor(const float);
		void SetDiffuseColor(const float, const float, const float);
		void SetSpecularReflection(const float);
		void SetSpecularExponent(const float);
		void SetSampler(std::shared_ptr<Sampler>);

	private:
		std::shared_ptr<Lambertian> m_Ambient;
		std::shared_ptr<Lambertian> m_Diffuse;
		std::shared_ptr<GlossySpecular> m_Specular;
};

inline void Phong::SetAmbientReflection(const float kdr) {
	m_Ambient->SetDiffuseReflection(kdr);
}

inline void Phong::SetDiffuseReflection(const float kdr) {
	m_Diffuse->SetDiffuseReflection(kdr);
}

inline void Phong::SetDiffuseColor(const RGBColor &color) {
	m_Ambient->SetDiffuseColor(color);
	m_Diffuse->SetDiffuseColor(color);
}

inline void Phong::SetDiffuseColor(const float color) {
	m_Ambient->SetDiffuseColor(color);
	m_Diffuse->SetDiffuseColor(color);
}

inline void Phong::SetDiffuseColor(const float r, const float g, const float b) {
	m_Ambient->SetDiffuseColor(r, g, b);
	m_Diffuse->SetDiffuseColor(r, g, b);
}

inline void Phong::SetSampler(std::shared_ptr<Sampler> sampler_ptr) {
	m_Ambient->SetSampler(sampler_ptr);
	m_Diffuse->SetSampler(sampler_ptr);
}

inline void Phong::SetSpecularReflection(const float ksr) {
	m_Specular->SetSpecularReflection(ksr);
}

inline void Phong::SetSpecularExponent(const float ksexp) {
	m_Specular->SetSpecularExponent(ksexp);
}

#endif
