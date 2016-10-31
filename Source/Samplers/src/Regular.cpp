#include "Regular.h"

Regular::Regular()
	: Sampler() {

}

Regular::Regular(const int numSamples)
	: Sampler(numSamples) {

	GenerateSamples();
}

Regular::Regular(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {

	GenerateSamples();
}

void Regular::GenerateSamples() {
	int n = static_cast<int>(sqrt(m_NumSamples));

	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				int x = (k + 0.5) / n;
				int y = (j + 0.5) / n;

				m_Samples.push_back( glm::vec2(x, y) );
			}
}
