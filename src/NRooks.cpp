#include "NRooks.h"

NRooks::NRooks()
	: Sampler()
{}

NRooks::NRooks(const int n)
	: Sampler(n) {

	generateSamples();
}

NRooks::NRooks(const NRooks &nr)
	: Sampler(nr) {

	generateSamples();
}

NRooks &NRooks::operator=(const NRooks &nr) {
	if (this == &nr)
		return (*this);

	Sampler::operator=(nr);

	return (*this);
}

NRooks *NRooks::clone() const {
	return (new NRooks(*this));

}

NRooks::~NRooks()
{}

void NRooks::generateSamples() {
	for (int i = 0; i < numSets; i++)
		for (int j = 0; j < numSamples; j++) {
			glm::vec2 point( (j + randFloat())/numSamples,  (j + randFloat())/numSamples );
			samples.push_back(point);
		}

	shuffle_X();
	shuffle_Y();
}
