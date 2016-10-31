#include "Plane.h"
#include "Ray.h"
#include "ShadeRecord.h"

Plane::Plane()
	: Object(),
	  m_Point(0.0f, 0.0f, 0.0f),
	  m_Normal(0.0f, 1.0f, 0.0f) {

}

Plane::Plane(const glm::vec3 &point, const glm::vec3 &normal)
	: Object(),
	  m_Point(point),
	  m_Normal(glm::normalize(normal)) {

}

bool Plane::Hit(const Ray &ray, double &tmin, ShadeRecord &sr) const {
	float t = glm::dot(m_Point - ray.m_Origin, m_Normal) / glm::dot(ray.m_Direction, m_Normal);

	if (t > kEpsilon) {
		tmin = t;
		sr.m_Normal = m_Normal;
		sr.m_HitPoint = ray.m_Origin + t * ray.m_Direction;

		return true;
	}

	return false;
}
