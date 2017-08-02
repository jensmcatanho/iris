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
#include "RayCast.h"
#include "Material.h"
#include "Surface.h"
#include "World.h"

RayCast::RayCast(std::shared_ptr<World> world_ptr) :
	Tracer(world_ptr) {

}

RGBColor RayCast::TraceRay(const Ray &ray) const {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);
	Surface sr(worldPtr->HitObjects(ray));

	if (sr.m_Hit) {
		sr.m_Ray = ray;
		return sr.m_MaterialPtr->Shade(sr);

	} else {
		return worldPtr->m_BackgroundColor;
	}
}