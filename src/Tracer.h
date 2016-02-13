#ifndef TRACER_H
#define TRACER_H

#include "Constants.h"
#include "Ray.h"
#include "RGBColor.h"
#include "ShadeRecord.h"

class World;

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
