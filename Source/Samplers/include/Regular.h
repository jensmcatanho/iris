#ifndef REGULAR_H
#define REGULAR_H

#include "Sampler.h"

class Regular : public Sampler {
	public:
		Regular();
		Regular(const int);
		Regular(const Regular &);
		Regular &operator=(const Regular &);
		virtual Regular *clone() const;

	private:
		virtual void generateSamples();
};

#endif
