#ifndef VIEWPLANE_H
#define VIEWPLANE_H

class ViewPlane {
	public:
		ViewPlane();
		ViewPlane(const ViewPlane&);
		ViewPlane& operator=(const ViewPlane&);
		~ViewPlane();

		void set_hres(const int h_res);
		void set_vres(const int v_res);
		void set_pixel_size(const float size);
		void set_gamma(const float g);
		void set_gamut_display(const bool show);
				
	public:
		int hres;
		int vres;
		float s; //pixel size

		float gamma;
		float inv_gamma;
		bool show_out_of_gamut;

};

inline void ViewPlane::set_hres(const int h_res) {
	hres = h_res;
}

inline void ViewPlane::set_vres(const int v_res) {
	vres = v_res;
}

inline void ViewPlane::set_pixel_size(const float size) {
	s = size;
}

inline void ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0 / gamma;
}

inline void ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}

#endif
