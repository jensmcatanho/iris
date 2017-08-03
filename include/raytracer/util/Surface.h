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
#ifndef SURFACE_H
#define SURFACE_H

#include "Prerequisites.h"
#include "Ray.h"
#include "RGBColor.h"

/**
 * @addtogroup Utilities
 * @{
 */

/**
 * Holds information about a surface.
 * @remarks TODO
 */
class Surface {
	public:
		/**
		 * Constructs a surface with a reference to the world.
		 * @param w Reference to the world.
		 */
		Surface(Scene &w);

		/**
		 * Checks if a ray has hit the surface.
		 */
		bool m_Hit;

		/**
		 * Material attached to the surface.
		 */
		std::shared_ptr<Material> m_MaterialPtr;

		/**
		 * Point where the surface has been hit by a ray.
		 */
		glm::vec3 m_HitPoint;

		/**
		 * Local point where the surface has been hit by a ray.
		 */
		glm::vec3 m_LocalHitPoint;

		/**
		 * Normal of the surface on the hit point.
		 */
		glm::vec3 m_Normal;

		/**
		 * Color of the surface.
		 */
		RGBColor m_Color;

		/**
		 * TODO
		 */
		Ray m_Ray;

		/**
		 * Recursion depth.
		 */
		int m_Depth;

		/**
		 * Ray parameter.
		 */
		double m_T;

		/**
		 * TODO
		 */
		glm::vec3 m_Direction;

		/**
		 * Reference to the world.
		 */
		Scene &w;
};

/**
 * @}
 */

#endif
