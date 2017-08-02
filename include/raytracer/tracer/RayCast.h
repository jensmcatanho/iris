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
#ifndef RAYCAST_H
#define RAYCAST_H

#include "Tracer.h"

/**
 * @addtogroup Tracers
 * @{
 */

/**
 * TODO.
 * @remarks TODO.
 */
class RayCast : public Tracer {
	public:
		/**
		 * Constructs a Tracer with a pointer to the world.
		 * @param world_ptr Pointer to the world.
		 */
		RayCast(std::shared_ptr<World> world_ptr);

		/**
		 * Standard ray tracing method.
		 * @param ray Ray traced.
		 * @return Color of the nearest surface hit by the ray.
		 */
		virtual RGBColor TraceRay(const Ray &ray) const;
};

/**
 * @}
 */

#endif