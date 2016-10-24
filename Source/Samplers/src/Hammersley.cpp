#include "Hammersley.h"

Hammersley::Hammersley()
	: Sampler() {

}

Hammersley::Hammersley(const int n)
	: Sampler(n) {

	generateSamples();
}

Hammersley::Hammersley(const Hammersley &h)
	: Sampler(h) {

	generateSamples();
}

Hammersley &Hammersley::operator=(const Hammersley &h) {
	if (this == &h)
		return (*this);

	Sampler::operator=(h);

	return (*this);
}

Hammersley *Hammersley::clone() const {
	return (new Hammersley(*this));

}

double Hammersley::phi(int j) {
	double x = 0.0;
	double f = 0.5;

	while (j) {
		x += f * (double)(j % 2);
		j /= 2;
		f *= 0.5;
	}

	return x;
}

void Hammersley::generateSamples() {
	for (int i = 0; i < numSets; i++)
		for (int j = 0; j < numSamples; j++) {
			glm::vec2 point( (float)j / (float)numSamples, phi(j) );
			samples.push_back(point);
		}
}
