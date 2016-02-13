#include "Tracer.h"
#include "World.h"

Tracer::Tracer()
	: worldPtr(nullptr)
{}

Tracer::Tracer(World  *wPtr)
	: worldPtr(wPtr)
{}

Tracer::~Tracer() {
	if (worldPtr)
		worldPtr = nullptr;
}

RGBColor Tracer::trace_ray(const Ray &ray) const {
	return RGBColor(BLACK);

}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
	return RGBColor(BLACK);

}




