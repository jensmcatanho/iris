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
#include "Pinhole.h"
#include "Ray.h"
#include "Sampler.h"
#include "Tracer.h"
#include "World.h"

Pinhole::Pinhole() :
	Camera(),
	m_vpDistance(500.0),
	m_Zoom(1.0) {

}

void Pinhole::RenderScene(const World &w) {
	Ray ray;
	RGBColor pixelColor;
	glm::vec2 samplePoint;
	ViewPlane vp(w.m_ViewPlane);

	ComputeUVW();

	vp.m_PixelSize /= m_Zoom;
	ray.m_Origin = m_Eye;

	for (int r = 0; r < vp.m_Height; r++) {
		for(int c = 0; c < vp.m_Width; c++) {
			pixelColor = RGBColor::Black;

			for (int i = 0; i < vp.m_NumSamples; i++) {
				samplePoint = vp.m_SamplerPtr->SampleUnitSquare();

				ray.m_Direction = RayDirection(glm::vec2(vp.m_PixelSize * (c - 0.5 * vp.m_Width + samplePoint.x),
														 vp.m_PixelSize * (r - 0.5 * vp.m_Height + samplePoint.y)));

				pixelColor += w.m_TracerPtr->TraceRay(ray);
			}

			pixelColor /= static_cast<float>(vp.m_NumSamples);
			pixelColor *= m_ExposureTime;
			w.DisplayPixel(r, c, pixelColor);
		}
	}
}

glm::vec3 Pinhole::RayDirection(const glm::vec2 &sample_point) const {
	glm::vec3 direction = glm::normalize(sample_point.x * m_U + sample_point.y * m_V - m_vpDistance * m_W);

	return direction;
}