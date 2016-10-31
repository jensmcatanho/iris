#include "Hammersley.h"

Hammersley::Hammersley()
	: Sampler() {

}

Hammersley::Hammersley(const int numSamples)
	: Sampler(numSamples) {

	GenerateSamples();
}

Hammersley::Hammersley(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {

	GenerateSamples();
}

double Hammersley::Phi(int j) const {
	// References: http://holger.dammertz.org/stuff/notes_HammersleyOnHemisphere.html
	// http://math.stackexchange.com/questions/849848/why-is-the-formula-for-generating-van-der-corput-sequences-called-an-inverse-rad
	double x = 0.0;
	double f = 0.5;

	while (j) {
		x += f * (double)(j % 2);
		j /= 2;
		f *= 0.5;
	}

	return x;
}

void Hammersley::GenerateSamples() {
	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < m_NumSamples; j++) {
			glm::vec2 point((float)j / (float)m_NumSamples, Phi(j));  //Pi = (xi, yi) = [1/n,	Phi2(i)]

			m_Samples.push_back(point);
		}
}
