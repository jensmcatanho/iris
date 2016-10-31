#include "Jittered.h"

Jittered::Jittered()
	: Sampler() {

}

Jittered::Jittered(const int numSamples)
	: Sampler(numSamples) {

	GenerateSamples();
}

Jittered::Jittered(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {

	GenerateSamples();
}

void Jittered::GenerateSamples() {
	int n = (int)sqrt(m_NumSamples);
	int x, y;

	for (int p = 0; p < m_NumSets; p++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				x = (k + RandFloat()) / n;
				y = (j + RandFloat()) / n;

				m_Samples.push_back( glm::vec2(x, y) );
			}
}
