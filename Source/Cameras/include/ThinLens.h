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
#ifndef THINLENS_H
#define THINLENS_H

#include "Camera.h"

class ThinLens : public Camera {
	public:
		ThinLens();
		
		virtual void RenderScene(const World &);

		void SetSampler(std::shared_ptr<Sampler>);
		void SetLensRadius(const float);
		void SetViewPlaneDistance(const float);
		void SetFocalPlaneDistance(const float);
		void SetZoom(const float);

	private:
		glm::vec3 RayDirection(const glm::vec2 &, const glm::vec2 &) const;

		std::shared_ptr<Sampler> m_SamplerPtr;

		float m_LensRadius;

		float m_vpDistance;

		float m_fpDistance;

		float m_Zoom;
};

inline void ThinLens::SetLensRadius(const float lens_radius) {
	m_LensRadius = lens_radius;
}

inline void ThinLens::SetViewPlaneDistance(const float vp_distance) {
	m_vpDistance = vp_distance;
}

inline void ThinLens::SetFocalPlaneDistance(const float fp_distance) {
	m_fpDistance = fp_distance;
}

inline void ThinLens::SetZoom(const float zoom) {
	float m_Zoom;
}

#endif