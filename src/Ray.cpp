#include "Ray.h"

Ray::Ray()
	: origin(0.0f, 0.0f, 0.0f), 
	  direction(1.0f, 1.0f, 1.0f) 
{}

Ray::Ray(glm::vec3 &o, glm::vec3 &d)
	: origin(o),
	  direction(d)
{}

Ray::Ray(const Ray &ray) 
	: origin(ray.origin),
	  direction(ray.direction)
{}

Ray::~Ray() 
{}

Ray &Ray::operator=(const Ray &ray) {
	if (this == &ray)
		return (*this);

	origin = ray.origin;
	direction = ray.direction;

	return (*this);
}
