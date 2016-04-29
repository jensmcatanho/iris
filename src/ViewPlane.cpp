#include "ViewPlane.h"
#include <iostream>

using namespace std;

ViewPlane::ViewPlane()							
	: hres(400), 
	  vres(400),
	  s(1.0),
	  gamma(1.0),
	  inv_gamma(1.0),
	  show_out_of_gamut(false),
	  numSamples(1)
{}

ViewPlane::ViewPlane(const ViewPlane& vp)   
	: hres(vp.hres),  
	  vres(vp.vres), 
	  s(vp.s),
	  gamma(vp.gamma),
	  inv_gamma(vp.inv_gamma),
	  show_out_of_gamut(vp.show_out_of_gamut),
	  numSamples(vp.numSamples) {
	
	if (vp.samplerPtr != NULL)
		samplerPtr = vp.samplerPtr->clone();
}

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

ViewPlane::~ViewPlane(void)
{}

void ViewPlane::setSamples(const int n) {
	numSamples = n;

	if (samplerPtr) {
		delete samplerPtr;
		samplerPtr = NULL;
	}

	if (numSamples > 1)
		samplerPtr = new MultiJittered(numSamples);
	else
		samplerPtr = new Regular(1);

}

void ViewPlane::setSampler(Sampler* sp) {
	//if (samplerPtr) {
	//	delete samplerPtr;
	//	samplerPtr = NULL;
	//}

	numSamples = sp->getNumSamples();
	samplerPtr = sp;

	//cout << "debug" << endl;
}
