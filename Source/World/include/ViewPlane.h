#ifndef VIEWPLANE_H
#define VIEWPLANE_H

#include "Sampler.h"
#include "MultiJittered.h"
#include "Regular.h"

class ViewPlane {
	public:
		ViewPlane();
		ViewPlane(const ViewPlane &);

		ViewPlane &operator=(const ViewPlane &);

		void setWidth(const int);
		void setHeight(const int);
		void setPixelSize(const float);
		void setGamma(const float);
		void setGamutDisplay(const bool);
		void setSamples(const int);
		void setSampler(Sampler*);
				
	public:
		int width;
		int height;
		float pixel_size;
		float gamma;
		float inv_gamma;
		bool out_of_gamut;
		int numSamples;
		Sampler* samplerPtr;

};

inline void ViewPlane::setWidth(const int new_w) {
	width = new_w;
}

inline void ViewPlane::setHeight(const int new_h) {
	height = new_h;
}

inline void ViewPlane::setPixelSize(const float size) {
	pixel_size = size;
}

inline void ViewPlane::setGamma(const float g) {
	gamma = g;
	inv_gamma = (float)(1.0 / gamma);
}

inline void ViewPlane::setGamutDisplay(const bool out) {
	out_of_gamut = out;
}

#endif