#include "Tracer.h"
#include "Ray.h"
#include "World.h"

Tracer::Tracer()
	: m_WorldPtr() {

}

Tracer::Tracer(std::shared_ptr<World> worldPtr)
	: m_WorldPtr(worldPtr) {

}

RGBColor Tracer::TraceRay(const Ray &ray) const {
	return RGBColor(RGBColor::Black);

}




