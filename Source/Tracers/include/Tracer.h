#ifndef TRACER_H
#define TRACER_H

#include "Prerequisites.h"

class Tracer {
	public:
		Tracer();
		Tracer(World *);
		virtual ~Tracer();

		virtual RGBColor trace_ray(const Ray &) const;
		virtual RGBColor trace_ray(const Ray, const int) const;

	protected:
		World *worldPtr;
};

#endif
