#include "ViewPlane.h"

ViewPlane::ViewPlane()							
	: hres(400), 
	  vres(400),
	  s(1.0),
	  gamma(1.0),
	  inv_gamma(1.0),
	  show_out_of_gamut(false)
{}

ViewPlane::ViewPlane(const ViewPlane& vp)   
	: hres(vp.hres),  
	  vres(vp.vres), 
	  s(vp.s),
	  gamma(vp.gamma),
	  inv_gamma(vp.inv_gamma),
	  show_out_of_gamut(vp.show_out_of_gamut)
{}

ViewPlane& ViewPlane::operator=(const ViewPlane& vp) {
	if (this == &vp)
		return (*this);
		
	hres = vp.hres;
	vres = vp.vres;
	s = vp.s;
	gamma = vp.gamma;
	inv_gamma = vp.inv_gamma;
	show_out_of_gamut = vp.show_out_of_gamut;
	
	return (*this);
}

ViewPlane::~ViewPlane(void) {}
