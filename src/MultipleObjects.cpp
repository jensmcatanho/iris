#include "MultipleObjects.h"

MultipleObjects::MultipleObjects()
	: Tracer()
{}

MultipleObjects::MultipleObjects(World* _worldPtr)
	: Tracer(_worldPtr)
{}

MultipleObjects::~MultipleObjects()
{}

RGBColor MultipleObjects::trace_ray(const Ray& ray) const {
	ShadeRec sr(worldPtr->hit_objects(ray));

	if (sr.hit)
		return sr.color;
	else
		return worldPtr->backgroundColor;
}
