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
