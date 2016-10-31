#ifndef JITTERED_H
#define JITTERED_H

#include "Sampler.h"

class Jittered : public Sampler {
	public:
		Jittered();

		// Constructs a Jittered sampler with the passed number of samples.
		Jittered(const int);

		// Constructs a Jittered sampler with the passed number of samples and sets.
		Jittered(const int, const int);

	private:
		virtual void GenerateSamples();
};

#endif
