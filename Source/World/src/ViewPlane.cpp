#include "ViewPlane.h"

#include "MultiJittered.h"
#include "Regular.h"
#include "Sampler.h"

ViewPlane::ViewPlane()							
	: width(400), 
	  height(400),
	  pixel_size(1.0),
	  gamma(1.0),
	  inv_gamma(1.0),
	  out_of_gamut(false),
	  numSamples(1) {

}

ViewPlane::ViewPlane(const ViewPlane &vp)   
	: width(vp.width),
	  height(vp.height),
	  pixel_size(vp.pixel_size),
	  gamma(vp.gamma),
	  inv_gamma(vp.inv_gamma),
	  out_of_gamut(vp.out_of_gamut),
	  numSamples(vp.numSamples) {
	
	if (vp.samplerPtr != NULL)
		samplerPtr = vp.samplerPtr->clone();

}

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
