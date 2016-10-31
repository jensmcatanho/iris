#ifndef MULTIJITTERED_H
#define MULTIJITTERED_H

#include "Sampler.h"

class MultiJittered : public Sampler {
	public:
		MultiJittered();

		// Constructs a MultiJittered sampler with the passed number of samples.
		MultiJittered(const int);

		// Constructs a MultiJittered sampler with the passed number of samples and sets.
		MultiJittered(const int, const int);

	private:
		virtual void GenerateSamples();
};

#endif
