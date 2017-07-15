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
#include "ThinLens.h"
#include "Ray.h"
#include "Sampler.h"
#include "Tracer.h"
#include "World.h"

ThinLens::ThinLens() :
	Camera(),
	m_LensRadius(1.0),
	m_fpDistance(500.0),
	m_vpDistance(500.0),
	m_Zoom(1.0) {

}

void ThinLens::RenderScene(const World &w) {
	Ray ray;
	RGBColor pixelColor;
	ViewPlane vp(w.m_ViewPlane);

	glm::vec2 us_samplePoint;  // Sample point on a unit square.
	glm::vec2 px_samplePoint;  // Sample point on a pixel.
	glm::vec2 ud_samplePoint;  // Sample point on a unit disk.
	glm::vec2 ln_samplePoint;  // Sample point on the lens.

	ComputeUVW();

	vp.m_PixelSize /= m_Zoom;

	for (int r = 0; r < vp.m_Height; r++) {
		for (int c = 0; c < vp.m_Width; c++) {
			pixelColor = RGBColor::Black;

			for (int i = 0; i < vp.m_NumSamples; i++) {
				us_samplePoint = vp.m_SamplerPtr->SampleUnitSquare();

				px_samplePoint.x = vp.m_PixelSize * (c - 0.5 * vp.m_Width + us_samplePoint.x);
				px_samplePoint.y = vp.m_PixelSize * (r - 0.5 * vp.m_Height + us_samplePoint.y);

				ud_samplePoint = m_SamplerPtr->SampleUnitDisk();
				ln_samplePoint = ud_samplePoint * m_LensRadius;

				ray.m_Origin = m_Eye + (ln_samplePoint.x * m_U) + (ln_samplePoint.y * m_V);
				ray.m_Direction = RayDirection(px_samplePoint, ln_samplePoint);

				pixelColor += w.m_TracerPtr->TraceRay(ray);
			}

			pixelColor /= vp.m_NumSamples;
			pixelColor *= m_ExposureTime;
			w.DisplayPixel(r, c, pixelColor);
		}
	}
}

void ThinLens::SetSampler(std::shared_ptr<Sampler> sampler_ptr) {
	m_SamplerPtr = sampler_ptr;
	m_SamplerPtr->MapToUnitDisk();
}

glm::vec3 ThinLens::RayDirection(const glm::vec2 &pixel_point, const glm::vec2 &lens_point) const {
	glm::vec2 fp_point(pixel_point.x * m_fpDistance / m_vpDistance,
		pixel_point.y * m_fpDistance / m_vpDistance);

	glm::vec3 direction = (fp_point.x - lens_point.x) * m_U +
		(fp_point.y - lens_point.y) * m_V -
		m_fpDistance * m_W;

	return glm::normalize(direction);
}