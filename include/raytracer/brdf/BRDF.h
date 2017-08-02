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
#ifndef BRDF_H
#define BRDF_H

#include "Prerequisites.h"
#include "RGBColor.h"

/**
 * @addtogroup BRDF
 * @{
 */

/**
 * The bidirectional reflectance distribution function abstraction.
 * @remarks TODO.
 */
class BRDF {
	public:
		/**
		 * Standard constructor.
		 */
		BRDF();

		/**
		 * Computes the reflected radiance along wo.
		 * @param  sr Information about the surface of the object.
		 * @param  wi Incoming light direction.
		 * @param  wo Reflected light direction.
		 * @return Reflected radiance of a surface.
		 */
		virtual RGBColor f(const Surface &sr, const glm::vec3 &wi, const glm::vec3 &wo) const;

		/**
		 * Computes the perfect diffuse reflectance.
		 * @param  sr Information about the surface of the object.
		 * @param  wo Reflected light direction.
		 * @return Perfect diffuse reflectance.
		 */
		virtual RGBColor rho(const Surface &sr, const glm::vec3 &wo) const;

		/**
		 * TODO.
		 * @param  sr Information about the surface of the object.
		 * @param  wi Incoming light direction.
		 * @param  wo Reflected light direction.
		 * @return 
		 */
		virtual RGBColor SampleF(Surface &sr, const glm::vec3 &wi, glm::vec3 &wo);

		/**
		 * TODO
		 * @param  sr  Information about the surface of the object.
		 * @param  wi  Incoming light direction.
		 * @param  wo  Reflected light direction.
		 * @param  pdf Probability density function.
		 * @return 
		 */
		virtual RGBColor SampleF(Surface &sr, const glm::vec3 &wi, glm::vec3 &wo, float &pdf);

		/**
		 * Sets a sampler to the BRDF.
		 * @param sampler_ptr Target sampler.
		 */
		void SetSampler(std::shared_ptr<Sampler>);

	protected:
		/**
		 * Pointer to the sampler attached to the BRDF object.
		 */
		std::shared_ptr<Sampler> m_SamplerPtr;
};

inline void BRDF::SetSampler(std::shared_ptr<Sampler> sampler_ptr) {
	m_SamplerPtr = sampler_ptr;
}

/**
 * @}
 */

#endif