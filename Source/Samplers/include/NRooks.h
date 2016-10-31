#ifndef NROOKS_H
#define NROOKS_H

#include "Sampler.h"

class NRooks : public Sampler {
	public:
		NRooks();

		// Constructs a n-Rooks sampler with the passed number of samples.
		NRooks(const int);

		// Constructs a n-Rooks sampler with the passed number of samples and sets.
		NRooks(const int, const int);

	private:
		virtual void GenerateSamples();
};

#endif
