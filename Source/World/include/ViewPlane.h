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

class ViewPlane {
	public:
		ViewPlane();

		void SetWidth(const int);
		void SetHeight(const int);
		void SetPixelSize(const float);
		void SetGamma(const float);
		void SetGamutDisplay(const bool);
		void SetSamples(const int);
		void SetSampler(std::shared_ptr<Sampler>);

		// Horizontal image resolution.
		int m_Width;

		// Vertical image resolution.
		int m_Height;

		float m_PixelSize;

		// Gamma correction factor.
		float m_Gamma;

		// Inverse of the gamma correction factor.
		float m_InvGamma;

		// Checks if RGBColor is out of gamut.
		bool m_OutOfGamut;

		std::shared_ptr<Sampler> m_SamplerPtr;
		
		// Number of samples per pixel.
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

#endif
