#ifndef HAMMERSLEY_H
#define HAMMERSLEY_H

#include "Sampler.h"

class Hammersley : public Sampler {
	public:
		Hammersley();

		// Constructs a Hammersley sampler with the passed number of samples.
		Hammersley(const int);

		// Constructs a Hammersley sampler with the passed number of samples and sets.
		Hammersley(const int, const int);

	private:
		virtual void GenerateSamples();

		// Radical-inverse function of an integer in base 2.
		double Phi(int) const;
};

#endif
