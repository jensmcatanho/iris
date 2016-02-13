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
	return RGBColor(0.0f, 0.0f, 0.0f);

}

RGBColor Tracer::trace_ray(const Ray ray, const int depth) const {
	return RGBColor(0.0f, 0.0f, 0.0f);

}




