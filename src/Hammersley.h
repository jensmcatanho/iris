#ifndef HAMMERSLEY_H
#define HAMMERSLEY_H

#include "Sampler.h"

class Hammersley : public Sampler {
	public:
		Hammersley();
		Hammersley(const int);
		Hammersley(const Hammersley &);

		Hammersley &operator=(const Hammersley &);
		virtual Hammersley *clone() const;

		virtual ~Hammersley();

		double phi(int);

	private:
		virtual void generateSamples();
};

#endif
