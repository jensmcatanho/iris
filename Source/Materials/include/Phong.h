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
		// Default constructor.
		Phong();

		// Return the color of an object at a given hit point.
		virtual RGBColor Shade(ShadeRecord &) const;

		// Define the reflection of the ambient component of the material.
		void SetAmbientReflection(const float);

		// Define the color of the ambient component of the material.
		void SetAmbientColor(const RGBColor &);

		// Define the reflection of the diffuse component of the material.
		void SetDiffuseReflection(const float);

		// Define the color of the diffuse component of the material.
		void SetDiffuseColor(const RGBColor &);

		// Define the reflection of the specular component of the material.
		void SetSpecularReflection(const float);

		// Define the color of the specular component of the material.
		void SetSpecularColor(const RGBColor &);

		// Define the specular factor of the specular component of the material.
		void SetSpecularExponent(const float);

		// Define the sampler to be used by all components of the material.
		void SetSampler(std::shared_ptr<Sampler>);

	private:
		// Ambient component of the material.
		std::shared_ptr<Lambertian> m_Ambient;

		// Diffuse component of the material.
		std::shared_ptr<Lambertian> m_Diffuse;

		// Specular component of the material.
		std::shared_ptr<GlossySpecular> m_Specular;
};

inline void Phong::SetAmbientReflection(const float kdr) {
	m_Ambient->SetDiffuseReflection(kdr);
}

inline void Phong::SetDiffuseColor(const RGBColor &color) {
	m_Ambient->SetDiffuseColor(color);
}

inline void Phong::SetDiffuseReflection(const float kdr) {
	m_Diffuse->SetDiffuseReflection(kdr);
}

inline void Phong::SetDiffuseColor(const RGBColor &color) {
	m_Diffuse->SetDiffuseColor(color);
}

inline void Phong::SetSampler(std::shared_ptr<Sampler> sampler_ptr) {
	m_Ambient->SetSampler(sampler_ptr);
	m_Diffuse->SetSampler(sampler_ptr);
}

inline void Phong::SetSpecularReflection(const float ksr) {
	m_Specular->SetSpecularReflection(ksr);
}

inline void Phong::SetSpecularColor(const RGBColor &color) {
	m_Specular = color;
}

inline void Phong::SetSpecularExponent(const float ksexp) {
	m_Specular->SetSpecularExponent(ksexp);
}

#endif
