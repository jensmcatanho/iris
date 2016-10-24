#ifndef MULTIPLEOBJECTS_H
#define MULTIPLEOBJECTS_H

#include "Tracer.h"
#include "World.h"

class MultipleObjects : public Tracer {
	public:
		MultipleObjects();
		MultipleObjects(World *);
		
		virtual RGBColor trace_ray(const Ray &) const;

};

#endif
