#include "Tracer.h"
#include "Ray.h"
#include "World.h"

Tracer::Tracer()
	: m_WorldPtr(nullptr) {

}

Tracer::Tracer(World *worldPtr)
	: m_WorldPtr(worldPtr) {

}

RGBColor Tracer::TraceRay(const Ray &ray) const {
	return RGBColor(RGBColor::Black);

}




