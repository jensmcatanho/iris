#ifndef REGULAR_H
#define REGULAR_H

#include "Sampler.h"

class Regular : public Sampler {
	public:
		Regular();

		// Constructs a Regular sampler with the passed number of samples.
		Regular(const int);

		// Constructs a Regular sampler with the passed number of samples and sets.
		Regular(const int, const int);

	private:
		virtual void GenerateSamples();
};

#endif
