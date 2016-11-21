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
#ifndef PINHOLE_H
#define PINHOLE_H

#include "Camera.h"

class Pinhole : public Camera {
	public:
		Pinhole();
		Pinhole(glm::vec3, glm::vec3);

		virtual void RenderScene(const World &);

		// Setters.
		void SetViewPlaneDistance(const float);
		void SetZoom(const float);

	private:
		// Calculates the ray direction given a sample point.
		glm::vec3 RayDirection(const glm::vec2 &) const;

		// Distance from the eye to the view plane.
		float m_vpDistance;

		// Zoom factor.
		float m_Zoom;
};

inline void Pinhole::SetViewPlaneDistance(const float distance) {
	m_vpDistance = distance;
}

inline void Pinhole::SetZoom(const float zoom) {
	m_Zoom = zoom;
}

#endif