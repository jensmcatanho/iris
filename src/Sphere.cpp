#include "Sphere.h"

Sphere::Sphere()
	: Object(),
	  center(0.0f, 0.0f, 0.0f),
	  radius(1.0f)
{}

Sphere::Sphere(glm::vec3 c, double r)
	: Object(),
	  center(c),
	  radius(r)
{}

Sphere::Sphere(const Sphere &sphere)
	: Object(sphere),
	  center(sphere.center),
	  radius(sphere.radius)
{}

Sphere::~Sphere()
{}

Sphere &Sphere::operator=(const Sphere &sphere) {
	if (this == &sphere)
		return (*this);

	Object::operator=(sphere);

	center = sphere.center;
	radius = sphere.radius;

	return (*this);
}

Sphere *Sphere::clone() const {
	return (new Sphere(*this));

}

bool Sphere::hit(const Ray &ray, double &tmin, ShadeRecord &sr) const {
	float t;
	glm::vec3 temp = ray.origin - center;
	double a = glm::dot(ray.direction, ray.direction);
	double b = glm::dot(2.0f * temp, ray.direction);
	double c = glm::dot(temp, temp) - radius * radius;
	double discriminant = b * b - (4 * a * c);

	if (discriminant < 0.0f)
		return false;

	t = (-b - sqrt(discriminant)) / 2 * a;

	if (t > kEpsilon) {
		tmin = t;
		sr.normal = temp + t * ray.direction;
		sr.normal = glm::vec3(sr.normal.x/radius, sr.normal.y/radius, sr.normal.z/radius);
		sr.hitPoint = ray.origin + glm::vec3(t * ray.direction.x, t * ray.direction.y, t * ray.direction.z);
		return true;

	}

	t = (-b + sqrt(discriminant)) / 2 * a;

	if (t > kEpsilon) {
		tmin = t;
		sr.normal = temp + t * ray.direction;
		sr.normal = glm::vec3(sr.normal.x/radius, sr.normal.y/radius, sr.normal.z/radius);
		sr.hitPoint = ray.origin + glm::vec3(t * ray.direction.x, t * ray.direction.y, t * ray.direction.z);
		return true;

	}

	return false;
}
