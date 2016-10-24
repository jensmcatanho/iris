#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
	public:
		Sphere();
		Sphere(glm::vec3, float);
		Sphere(const Sphere &);
		Sphere &operator=(const Sphere &);

		virtual bool hit(const Ray &, double &, ShadeRecord &) const;
		void setCenter(const glm::vec3 &);
		void setRadius(const float);

	public:
		glm::vec3 center;
		float radius;

};

inline void Sphere::setCenter(const glm::vec3 &c) {
	center = c;
}
		
inline void Sphere::setRadius(const float r) {
	radius = r;
}

#endif
