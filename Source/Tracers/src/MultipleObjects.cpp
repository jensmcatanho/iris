#include "MultipleObjects.h"

MultipleObjects::MultipleObjects()
	: Tracer() {

}

MultipleObjects::MultipleObjects(World *wPtr)
	: Tracer(wPtr) {

}

RGBColor MultipleObjects::trace_ray(const Ray &ray) const {
	ShadeRecord sr(worldPtr->hitObjects(ray));

	if (sr.hit)
		return sr.color;
	else
		return worldPtr->backgroundColor;
}
