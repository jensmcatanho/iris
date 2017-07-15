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
#include "RGBColor.h"

/**
 * @addtogroup Lights
 * @{
 */

/**
 * Representation of a light source.
 * @remarks TODO
 */
class Light {
	public:
		/**
		 * Standard constructor.
		 */
		Light();

		/**
		 * Computes the direction of the incoming light at a given surface.
		 * @param  sr Information about the surface of the object.
		 * @return Direction from which the light arrives at the surface.
		 */
		virtual glm::vec3 GetDirection(Surface &sr) = 0;

		/**
		 * Computes the incident radiance at a given surface.
		 * @param sr Information about the surface of the object.
		 * @return Incident radiance at the surface.
		 */
		virtual RGBColor L(Surface &sr);

		/**
		 * Checks if a surface is shadowed by another object.
		 * @param  ray Casted shadow ray.
		 * @param  sr  Information about the surface of the object.
		 * @return True, if the surface is shadowed.
		 */
		virtual bool Shadowed(const Ray &ray, const Surface &sr) const = 0;

		/**
		 * Sets if the objects illuminated by the light cast shadows over other objects.
		 * @param flag Flag that sets if the objects illuminates by the light cast shadows.
		 */
		void CastsShadows(bool flag);

		/**
		 * Checks if the objects illuminated by the light cast shadows over other objects.
		 * @return True, if the objects illuminated by the light cast shadows.
		 */
		bool CastsShadows() const;

	protected:
		/**
		 * Flag that stores information about whether the objects illuminated by the light casts shadows over other objects.
		 */
		bool m_Shadows;

};

inline void Light::CastsShadows(bool flag) {
	m_Shadows = flag;
}

inline bool Light::CastsShadows() const {
	return m_Shadows;
}

/**
 * @}
 */

#endif