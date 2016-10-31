#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
	public:
		Sphere();
		Sphere(glm::vec3, float);

		// Check if a ray intersects with this Object and returns it's shading information.
		virtual bool Hit(const Ray &, double &, ShadeRecord &) const;

		void SetCenter(const glm::vec3 &);
		void SetRadius(const float);

	public:
		glm::vec3 m_Center;
		float m_Radius;

};

inline void Sphere::SetCenter(const glm::vec3 &center) {
	m_Center = center;
}
		
inline void Sphere::SetRadius(const float radius) {
	m_Radius = radius;
}

#endif
