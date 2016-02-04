#include "Tracer.h"
#include "World.h"

Tracer::Tracer(void)
	: worldPtr(NULL)
{}

Tracer::Tracer(World* _worldPtr)
	: worldPtr(_worldPtr)
{}

Tracer::~Tracer(void) {
	if (worldPtr)
		worldPtr = NULL;
}

RGBColor Tracer::trace_ray(const Ray& ray) const {
	return RGBColor(0.0f, 0.0f, 0.0f);

}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
	return RGBColor(0.0f, 0.0f, 0.0f);

}




