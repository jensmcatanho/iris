#ifndef NROOKS_H
#define NROOKS_H

#include "Sampler.h"

class NRooks : public Sampler {
	public:
		NRooks();
		NRooks(const int);
		NRooks(const NRooks &);
		NRooks &operator=(const NRooks &);
		virtual NRooks *clone() const;

	private:
		virtual void generateSamples();
};

#endif
