#ifndef PURERANDOM_H
#define PURERANDOM_H

#include "Sampler.h"

class PureRandom : public Sampler {
	public:
		PureRandom();

		// Constructs a PureRandom sampler with the passed number of samples.
		PureRandom(const int);

		// Constructs a PureRandom sampler with the passed number of samples and sets.
		PureRandom(const int, const int);

	private:
		virtual void GenerateSamples();
};

#endif
