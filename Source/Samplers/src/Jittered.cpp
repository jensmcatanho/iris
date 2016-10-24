#include "Jittered.h"

Jittered::Jittered()
	: Sampler() {

}

Jittered::Jittered(const int numSp)
	: Sampler(numSp) {

	generateSamples();
}

Jittered::Jittered(const int numSp, const int numSt)
	: Sampler(numSp, numSt) {

	generateSamples();
}

Jittered::Jittered(const Jittered &j)
	: Sampler(j) {

	generateSamples();
}

Jittered &Jittered::operator=(const Jittered &j) {
	if (this == &j)
		return (*this);

	Sampler::operator=(j);

	return (*this);
}

Jittered *Jittered::clone() const {
	return (new Jittered(*this));

}

void Jittered::generateSamples() {
	int n = (int)sqrt(numSamples);
	int x, y;

	for (int p = 0; p < numSets; p++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				x = (k + randFloat()) / n;
				y = (j + randFloat()) / n;

				samples.push_back( glm::vec2(x, y) );
			}
}
