#ifndef SINGLESPHERE_H
#define SINGLESPHERE_H

#include "Tracer.h"
#include "World.h"

class SingleSphere : public Tracer {
	public:
		SingleSphere();
		SingleSphere(World*);
		virtual ~SingleSphere();
		virtual RGBColor trace_ray(const Ray&) const;

};

#endif
