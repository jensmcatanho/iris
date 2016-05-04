#ifndef MULTIJITTERED_H
#define MULTIJITTERED_H

#include "Sampler.h"

class MultiJittered : public Sampler {
	public:
		MultiJittered();
		MultiJittered(const int);
		MultiJittered(const int, const int);
		MultiJittered(const MultiJittered &);

		MultiJittered &operator=(const MultiJittered &);
		virtual MultiJittered *clone() const;

		virtual ~MultiJittered();

	private:
		virtual void generateSamples();
};

#endif
