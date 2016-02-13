#include "ViewPlane.h"

ViewPlane::ViewPlane()							
	: width(400), 
	  height(400),
	  pixel_size(1.0),
	  gamma(1.0),
	  inv_gamma(1.0),
	  out_of_gamut(false)
{}

ViewPlane::ViewPlane(const ViewPlane &vp)   
	: width(vp.width),
	  height(vp.height),
	  pixel_size(vp.pixel_size),
	  gamma(vp.gamma),
	  inv_gamma(vp.inv_gamma),
	  out_of_gamut(vp.out_of_gamut)
{}

ViewPlane::~ViewPlane()
{}

ViewPlane &ViewPlane::operator=(const ViewPlane &vp) {
	if (this == &vp)
		return (*this);
		
	width = vp.width;
	height = vp.height;
	pixel_size = vp.pixel_size;
	gamma = vp.gamma;
	inv_gamma = vp.inv_gamma;
	out_of_gamut = vp.out_of_gamut;
	
	return (*this);
}
