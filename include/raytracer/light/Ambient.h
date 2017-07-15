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
#ifndef AMBIENT_H
#define AMBIENT_H

#include "Light.h"

/**
 * @addtogroup Lights
 * @{
 */

/**
 * Representation of an ambient light source.
 * @remarks TODO
 */
class Ambient : public Light {
	public:
		/**
		 * Standard constructor.
		 */
		Ambient();

		/**
		 * Computes the direction of the incoming light at a given surface.
		 * @param  sr Information about the surface of the object.
		 * @return Direction from which the light arrives at the surface.
		 */
		virtual glm::vec3 GetDirection(Surface &sr);

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
		virtual bool Shadowed(const Ray &ray, const Surface &sr) const;

		/**
		 * Sets the intensity of the light.
		 * @param intensity Target intensity.
		 */
		void SetIntensity(const float intensity);

		/**
		 * Sets the color of the light.
		 * @param color Target color.
		 */
		void SetColor(const RGBColor &color);

	private:
		/**
		 * Radiance scaling factor.
		 */
		float m_Intensity;

		/**
		 * Color of the light.
		 */
		RGBColor m_Color;
};

inline void Ambient::SetIntensity(const float intensity) {
	m_Intensity = intensity;
}

inline void Ambient::SetColor(const RGBColor &color) {
	m_Color = color;
}

/**
 * @}
 */

#endif