#include "NRooks.h"

NRooks::NRooks()
	: Sampler() {

}

NRooks::NRooks(const int numSamples)
	: Sampler(numSamples) {

	GenerateSamples();
}

NRooks::NRooks(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {

	GenerateSamples();
}

void NRooks::GenerateSamples() {
	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < m_NumSamples; j++) {
			float x = (j + RandFloat()) / m_NumSamples;
			float y = (j + RandFloat()) / m_NumSamples;		
			
			glm::vec2 point(x, y);
			m_Samples.push_back(point);
		}

	ShuffleX();
	ShuffleY();
}
