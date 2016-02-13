#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"

class Sphere : public Object {
	public:
		Sphere();
		Sphere(glm::vec3, double);
		Sphere(const Sphere &);
		virtual ~Sphere();

		Sphere &operator=(const Sphere &);
		virtual Sphere *clone() const;

		virtual bool hit(const Ray &, double &, ShadeRecord &) const;
		void setCenter(const glm::vec3 &);
		void setRadius(const double);

	public:
		glm::vec3 center;
		double radius;
		static const double kEpsilon;

};

inline void Sphere::setCenter(const glm::vec3 &c) {
	center = c;
}
		
inline void Sphere::setRadius(const double r) {
	radius = r;
}

#endif
