#include "SingleSphere.h"

SingleSphere::SingleSphere()
	: Tracer()
{}

SingleSphere::SingleSphere(World* worldPtr)
	: Tracer(worldPtr)
{}

SingleSphere::~SingleSphere()
{}

RGBColor SingleSphere::trace_ray(const Ray& ray) const {
	ShadeRec sr(*worldPtr);
	double t;

	if (worldPtr->sphere.hit(ray, t, sr))
		return RGBColor(1.0f, 0.0f, 0.0f);
	else
		return RGBColor(0.0f, 0.0f, 0.0f);
}
