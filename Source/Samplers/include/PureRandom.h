#ifndef PURERANDOM_H
#define PURERANDOM_H

#include "Sampler.h"

class PureRandom : public Sampler {
	public:
		PureRandom();
		PureRandom(const int);
		PureRandom(const PureRandom &);
		PureRandom &operator=(const PureRandom &);
		virtual PureRandom *clone() const;

	private:
		virtual void generateSamples();
};

#endif
