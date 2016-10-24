#include "PureRandom.h"

PureRandom::PureRandom()
	: Sampler() {

}

PureRandom::PureRandom(const int numSp)
	: Sampler(numSp) {

	generateSamples();
}

PureRandom::PureRandom(const PureRandom &pr)
	: Sampler(pr) {

	generateSamples();
}

PureRandom &PureRandom::operator=(const PureRandom &pr) {
	if (this == &pr)
		return (*this);

	Sampler::operator=(pr);

	return (*this);
}

PureRandom *PureRandom::clone() const {
	return (new PureRandom(*this));

}

void PureRandom::generateSamples() {
	for (int p = 0; p < numSets; p++)
		for (int q = 0; q < numSamples; q++)
			samples.push_back(glm::vec2(randFloat(), randFloat()));
}
