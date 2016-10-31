#include "Sphere.h"
#include "Ray.h"
#include "ShadeRecord.h"

Sphere::Sphere()
	: Object(),
	  m_Center(0.0f, 0.0f, 0.0f),
	  m_Radius(1.0f) {

}

Sphere::Sphere(glm::vec3 c, float r)
	: Object(),
	  m_Center(c),
	  m_Radius(r) {

}

bool Sphere::Hit(const Ray &ray, double &tmin, ShadeRecord &sr) const {
	float t;
	glm::vec3 temp = ray.m_Origin - m_Center;
	double a = glm::dot(ray.m_Direction, ray.m_Direction);
	double b = glm::dot(2.0f * temp, ray.m_Direction);
	double c = glm::dot(temp, temp) - m_Radius * m_Radius;
	double discriminant = b * b - (4 * a * c);

	if (discriminant < 0.0f)
		return false;

	t = (float)((-b - sqrt(discriminant)) / 2 * a);

	if (t > kEpsilon) {
		tmin = t;
		sr.m_Normal = temp + t * ray.m_Direction;
		sr.m_Normal = sr.m_Normal * (1.0f / m_Radius);
		sr.m_HitPoint = ray.m_Origin + ray.m_Direction * t;
		return true;

	}

	t = (float)((-b + sqrt(discriminant)) / 2 * a);

	if (t > kEpsilon) {
		tmin = t;
		sr.m_Normal = temp + t * ray.m_Direction;
		sr.m_Normal = sr.m_Normal * (1.0f / m_Radius);
		sr.m_HitPoint = ray.m_Origin + ray.m_Direction * t;
		return true;

	}

	return false;
}
