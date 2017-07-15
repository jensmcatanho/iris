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

/**
 * @addtogroup BRDF
 * @{
 */

/**
 * The glossy specular bidirectional reflectance distribution function abstraction.
 * @remarks TODO.
 */
class GlossySpecular : public BRDF {
	public:
		/**
		 * Standard constructor.
		 */
		GlossySpecular();

		/**
		 * Computes the reflected radiance along wo.
		 * @param  sr Information about the surface of the object.
		 * @param  wi Incoming light direction.
		 * @param  wo Reflected light direction.
		 * @return Reflected radiance of a surface.
		 */
		virtual RGBColor f(const Surface &sr, const glm::vec3 &wi, const glm::vec3 &wo) const;

		/**
		 * Sets the specular reflection coefficient.
		 * @param ksr Target specular reflection coefficient.
		 */
		void SetSpecularReflection(const float ksr);

		/**
		 * Sets the specular color.
		 * @param color Target specular color.
		 */
		void SetSpecularColor(const RGBColor &color);

		/**
		 * Sets the specular exponent.
		 * @param ksexp Target specular exponent.
		 */
		void SetSpecularExponent(const float ksexp);

	private:
		/**
		 * Specular reflection coefficient.
		 */
		float m_SpecularReflection;

		/**
		 * Specular color.
		 */
		RGBColor m_SpecularColor;

		/**
		 * Specular exponent.
		 */
		float m_SpecularExp;
};

inline void GlossySpecular::SetSpecularReflection(const float ksr) {
	m_SpecularReflection = ksr;
}

inline void GlossySpecular::SetSpecularColor(const RGBColor &color) {
	m_SpecularColor = color;
}

inline void GlossySpecular::SetSpecularExponent(const float ksexp) {
	m_SpecularExp = ksexp;
}

/**
 * @}
 */

#endif