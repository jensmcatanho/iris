#include "Plane.h"

Plane::Plane()
	: Object(),
	  point(0.0f, 0.0f, 0.0f),
	  normal(0.0f, 1.0f, 0.0f)
{}

Plane::Plane(const glm::vec3 &p, const glm::vec3 &n)
	: Object(),
	  point(p),
	  normal(glm::normalize(n))
{}

Plane::Plane(const Plane &plane)
	: Object(plane),
	  point(plane.point),
	  normal(plane.normal)
{}

Plane *Plane::clone() const {
	return (new Plane(*this));

}

Plane &Plane::operator=(const Plane &plane) {
	if (this == &plane)
		return (*this);

	Object::operator=(plane);

	point = plane.point;
	normal = plane.normal;

	return (*this);
}

Plane::~Plane()
{}

bool Plane::hit(const Ray &ray, double &tmin, ShadeRecord &sr) const {
	float t = glm::dot(point - ray.origin, normal) / glm::dot(ray.direction, normal);

	if (t > kEpsilon) {
		tmin = t;
		sr.normal = normal;
		sr.hitPoint = ray.origin + t * ray.direction;

		return true;
	}

	return false;
}
