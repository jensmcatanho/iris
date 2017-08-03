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
#include "Orthographic.h"
#include "Ray.h"
#include "Sampler.h"
#include "Tracer.h"
#include "World.h"

Orthographic::Orthographic() :
	Camera(),
	m_vpDistance(100.0),
	m_Zoom(1.0) {

}

void Orthographic::RenderScene(const World &w) {
	Ray ray;
	RGBColor pixel_color;
	glm::vec2 sample_point;
	ProjectionPlane vp(w.m_ProjectionPlane);

	ComputeUVW();

	ray.m_Direction = glm::vec3(0.0f, 0.0f, -1.0f);
	vp.m_PixelSize /= m_Zoom;
	
	for (int r = 0; r < vp.m_Height; r++) {
		for (int c = 0; c <= vp.m_Width; c++) {
			pixel_color = RGBColor::Black;

			for (int i = 0; i < vp.m_NumSamples; i++) {
				sample_point = vp.m_SamplerPtr->SampleUnitSquare();
				ray.m_Origin = glm::vec3(vp.m_PixelSize * (c - 0.5 * vp.m_Width + sample_point.x),
					vp.m_PixelSize * (r - 0.5 * vp.m_Height + sample_point.y), m_vpDistance);
				pixel_color += w.m_TracerPtr->TraceRay(ray);

			}

			pixel_color /= static_cast<float>(vp.m_NumSamples);
			pixel_color *= m_ExposureTime;
			w.DisplayPixel(r, c, pixel_color);
		}
	}
}