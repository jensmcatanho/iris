#include "PureRandom.h"

PureRandom::PureRandom()
	: Sampler() {

}

PureRandom::PureRandom(const int numSamples)
	: Sampler(numSamples) {

	GenerateSamples();
}

PureRandom::PureRandom(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {

	GenerateSamples();
}

void PureRandom::GenerateSamples() {
	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < m_NumSamples; j++)
			m_Samples.push_back(glm::vec2( RandFloat(), RandFloat() ));
}
