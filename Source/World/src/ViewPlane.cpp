#include "ViewPlane.h"

#include "MultiJittered.h"
#include "Regular.h"
#include "Sampler.h"

ViewPlane::ViewPlane()							
	: m_Width(400), 
	  m_Height(400),
	  m_PixelSize(1.0),
	  m_Gamma(1.0),
	  m_InvGamma(1.0),
	  m_OutOfGamut(false),
	  m_NumSamples(1) {

}

void ViewPlane::SetSamples(const int numSamples) {
	m_NumSamples = numSamples;

	if (m_NumSamples > 1) {
		std::shared_ptr<MultiJittered> newSampler(new MultiJittered(numSamples));
		m_SamplerPtr = newSampler;
	
	} else {
		std::shared_ptr<Regular> newSampler(new Regular(1));
		m_SamplerPtr = newSampler;

	}
}

void ViewPlane::SetSampler(std::shared_ptr<Sampler> samplerPtr) {
	m_SamplerPtr = samplerPtr;
	m_NumSamples = samplerPtr->GetNumOfSamples();
}
