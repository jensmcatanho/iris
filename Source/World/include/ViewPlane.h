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
#ifndef VIEWPLANE_H
#define VIEWPLANE_H

#include "Prerequisites.h"

/**
 * @addtogroup World
 * @{
 */

/**
 * The plane in which the scene is rendered.
 * @remarks TODO.
 */
class ViewPlane {
	public:
		/**
		 * Standard constructor.
		 */
		ViewPlane();

		/**
		 * Sets the width of the view plane.
		 * @param width Target width.
		 */
		void SetWidth(const int width);

		/**
		 * Sets the height of the view plane.
		 * @param height Target height.
		 */
		void SetHeight(const int height);

		/**
		 * Sets the pixel size of the view plane.
		 * @param pixel_size Target pixel size.
		 */
		void SetPixelSize(const float pixel_size);

		/**
		 * Sets the gamma correction factor of the view plane.
		 * @param gamma Target gamma correction factor.
		 */
		void SetGamma(const float gamma);

		/**
		 * Sets how to deal with out of gamut colors.
		 * @param out_of_gamut Target out of gamut.
		 */
		void SetGamutDisplay(const bool out_of_gamut);

		/**
		 * Sets the sampler used by the plane.
		 * @param sampler_ptr Target sampler.
		 */
		void SetSampler(std::shared_ptr<Sampler> sampler_ptr);

		/**
		 * Sets the number of samples used by the view plane.
		 * @param numSamples Target number of samples.
		 */
		void SetSamples(const int numSamples);

		/**
		 * Horizontal image resolution.
		 */
		int m_Width;

		/**
		 * Vertical image resolution.
		 */
		int m_Height;

		/**
		 * Pixel size.
		 */
		float m_PixelSize;

		/**
		 * Gamma correction factor.
		 */
		float m_Gamma;

		/**
		 * Inverse of the gamma correction factor.
		 */
		float m_InvGamma;

		/**
		 * Checks if RGBColor is out of gamut.
		 */
		bool m_OutOfGamut;

		/**
		 * Smart pointer to a sampler.
		 */
		std::shared_ptr<Sampler> m_SamplerPtr;
		
		/**
		 * Number of samples per pixel.
		 */
		int m_NumSamples;
};

inline void ViewPlane::SetWidth(const int width) {
	m_Width = width;
}

inline void ViewPlane::SetHeight(const int height) {
	m_Height = height;
}

inline void ViewPlane::SetPixelSize(const float pixel_size) {
	m_PixelSize = pixel_size;
}

inline void ViewPlane::SetGamma(const float gamma) {
	m_Gamma = gamma;
	m_InvGamma = static_cast<float>(1.0 / gamma);
}

inline void ViewPlane::SetGamutDisplay(const bool out_of_gamut) {
	m_OutOfGamut = out_of_gamut;
}

/**
 * @}
 */

#endif
