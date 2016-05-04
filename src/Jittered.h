#ifndef JITTERED_H
#define JITTERED_H

#include "Sampler.h"

class Jittered : public Sampler {
	public:
		Jittered();
		Jittered(const int);
		Jittered(const int, const int);
		Jittered(const Jittered &);

		Jittered &operator=(const Jittered &);
		virtual Jittered *clone() const;

		virtual ~Jittered();

	private:
		virtual void generateSamples();
};

#endif
