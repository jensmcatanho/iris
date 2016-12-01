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
#ifndef LIGHT_H
#define LIGHT_H

#include "Prerequisites.h"

class Light {
	public:
		/**
		 * Default constructor.
		 */
		Light();

		/**
		 * Computes the normalized direction from a hit point to the light.
		 * @param {Surface &} sr Shading record of a surface.
		 * @return {glm::vec3}
		 */
		virtual glm::vec3 GetDirection(Surface &) = 0;

		/**
		 * @param {Surface &}
		 * @return {RGBColor}
		 */
		virtual RGBColor L(Surface &);

		/**
		 * @param
		 * @return {bool}
		 */
		virtual bool Shadowed(const Ray &, const Surface &) const = 0;

		/**
		 * Sets if the object casts shadows over other objects.
		 * @param {bool} flag Cast shadows flag.
		 */
		void CastsShadows(bool);

		/**
		 * Checks if the object casts shadows over other objects.
		 * @return {bool}
		 */
		bool CastsShadows() const;

	protected:
		/**
		 * Flag that stores information about whether the light casts shadows.
		 * @type {bool}
		 */
		bool m_Shadows;

};

inline void Light::CastsShadows(bool flag) {
	m_Shadows = flag;
}

inline bool Light::CastsShadows() const {
	return m_Shadows;
}

#endif