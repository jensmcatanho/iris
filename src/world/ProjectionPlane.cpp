/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016-2017 Jean Michel Catanho

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
#include "ProjectionPlane.h"

#include "MultiJittered.h"
#include "Regular.h"
#include "Sampler.h"

ProjectionPlane::ProjectionPlane() :
	m_Width(400), 
	m_Height(400),
	m_PixelSize(1.0),
	m_Gamma(1.0),
	m_InvGamma(1.0),
	m_ClampOutOfGamut(false),
	m_ClampColor(1.0),
	m_NumSamples(1) {

}

void ProjectionPlane::SetSamples(const int numSamples) {
	m_NumSamples = numSamples;

	if (m_NumSamples > 1) {
		std::shared_ptr<MultiJittered> newSampler(new MultiJittered(numSamples));
		m_SamplerPtr = newSampler;
	
	} else {
		std::shared_ptr<Regular> newSampler(new Regular(1));
		m_SamplerPtr = newSampler;

	}
}

void ProjectionPlane::SetSampler(std::shared_ptr<Sampler> sampler_ptr) {
	m_SamplerPtr = sampler_ptr;
	m_NumSamples = sampler_ptr->GetNumOfSamples();
}
