/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016-2017 Jean Michel Catanho

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
#ifndef PLASTIC_H
#define PLASTIC_H

#include "Material.h"

/**
 * @addtogroup Materials
 * @{
 */

/**
 * Rendering properties of an object.
 * @remarks TODO.
 * @see Lambertian
 * @see Phong
 */
class Plastic : public Material {
	public:
		/**
		 * Standard constructor.
		 */
		Plastic();

		/**
		 * Computes the color of a given surface.
		 * @param  sr Information about the surface of the object.
		 * @return Color of the surface.
		 */
		virtual RGBColor Shade(Surface &sr) const;

		/**
		* Sets the BRDF of the ambient component of the material.
		* @param kdr Target diffuse reflection.
		*/
		void SetAmbientBRDF(std::shared_ptr<BRDF> ambient_brdf);

		/**
		* Sets the BRDF of the diffuse component of the material.
		* @param kdr Target diffuse reflection.
		*/
		void SetDiffuseBRDF(std::shared_ptr<BRDF> diffuse_brdf);

		/**
		* Sets the BRDF of the specular component of the material.
		* @param kdr Target diffuse reflection.
		*/
		void SetSpecularBRDF(std::shared_ptr<BRDF> specular_brdf);

		/**
		 * Sets the sampler to be used by the BRDFs of the material.
		 * @param sampler_ptr Target sampler.
		 */
		void SetSampler(std::shared_ptr<Sampler>);

	private:
		/**
		 * Ambient BRDF of the material.
		 */
		std::shared_ptr<BRDF> m_Ambient;

		/**
		 * Diffuse BRDF of the material.
		 */
		std::shared_ptr<BRDF> m_Diffuse;

		/**
		 * Specular BRDF of the material.
		 */
		std::shared_ptr<BRDF> m_Specular;
};

inline void Plastic::SetAmbientBRDF(std::shared_ptr<BRDF> ambient_brdf) {
	m_Ambient = ambient_brdf;
}

inline void Plastic::SetDiffuseBRDF(std::shared_ptr<BRDF> diffuse_brdf) {
	m_Diffuse = diffuse_brdf;
}

inline void Plastic::SetSpecularBRDF(std::shared_ptr<BRDF> specular_brdf) {
	m_Specular = specular_brdf;
}

inline void Plastic::SetSampler(std::shared_ptr<Sampler> sampler_ptr) {
	m_Ambient->SetSampler(sampler_ptr);
	m_Diffuse->SetSampler(sampler_ptr);
}

/**
 * @}
 */

#endif
