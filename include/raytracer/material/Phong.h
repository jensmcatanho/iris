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

/**
 * @addtogroup Materials
 * @{
 */

/**
 * Rendering properties of an object.
 * @remarks TODO.
 * @see Lambertian
 * @see GlossySpecular
 */
class Phong : public Material {
	public:
		/**
		 * Standard constructor.
		 */
		Phong();

		/**
		 * Computes the color of a given surface.
		 * @param  sr Information about the surface of the object.
		 * @return Color of the surface.
		 */
		virtual RGBColor Shade(Surface &sr) const;

		/**
		 * Sets the diffuse reflection of the ambient component of the material.
		 * @param kdr Target diffuse reflection.
		 */
		void SetAmbientReflection(const float kdr);

		/**
		 * Sets the diffuse color of the ambient component of the material.
		 * @param color Target diffuse color.
		 */
		void SetAmbientColor(const RGBColor &color);

		/**
		 * Sets the diffuse reflection of the diffuse component of the material.
		 * @param kdr Target diffuse reflection.
		 */
		void SetDiffuseReflection(const float kdr);

		/**
		 * Sets the diffuse color of the diffuse component of the material.
		 * @param color Target diffuse color.
		 */
		void SetDiffuseColor(const RGBColor &color);

		/**
		 * Sets the specular reflection of the specular component of the material.
		 * @param kdr Target specular reflection.
		 */
		void SetSpecularReflection(const float kdr);

		/**
		 * Sets the specular color of the specular component of the material.
		 * @param color Target specular color.
		 */
		void SetSpecularColor(const RGBColor &color);

		/**
		 * Sets the specular factor of the specular component of the material.
		 * @param ksexp Target specular factor.
		 */
		void SetSpecularExponent(const float ksexp);

		/**
		 * Sets the sampler to be used by the BRDFs of the material.
		 * @param sampler_ptr Target sampler.
		 */
		void SetSampler(std::shared_ptr<Sampler>);

	private:
		/**
		 * Ambient BRDF of the material.
		 */
		std::shared_ptr<Lambertian> m_Ambient;

		/**
		 * Diffuse BRDF of the material.
		 */
		std::shared_ptr<Lambertian> m_Diffuse;

		/**
		 * Specular BRDF of the material.
		 */
		std::shared_ptr<GlossySpecular> m_Specular;
};

inline void Phong::SetAmbientReflection(const float kdr) {
	m_Ambient->SetDiffuseReflection(kdr);
}

inline void Phong::SetAmbientColor(const RGBColor &color) {
	m_Ambient->SetDiffuseColor(color);
}

inline void Phong::SetDiffuseReflection(const float kdr) {
	m_Diffuse->SetDiffuseReflection(kdr);
}

inline void Phong::SetDiffuseColor(const RGBColor &color) {
	m_Diffuse->SetDiffuseColor(color);
}

inline void Phong::SetSpecularReflection(const float ksr) {
	m_Specular->SetSpecularReflection(ksr);
}

inline void Phong::SetSpecularColor(const RGBColor &color) {
	m_Specular->SetSpecularColor(color);
}

inline void Phong::SetSpecularExponent(const float ksexp) {
	m_Specular->SetSpecularExponent(ksexp);
}

inline void Phong::SetSampler(std::shared_ptr<Sampler> sampler_ptr) {
	m_Ambient->SetSampler(sampler_ptr);
	m_Diffuse->SetSampler(sampler_ptr);
}

/**
 * @}
 */

#endif
