#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {
	public:
		Plane();
		Plane(const glm::vec3&, const glm::vec3&);
		Plane(const Plane&);
		virtual Plane* clone() const;
		Plane& operator=(const Plane&);
		virtual ~Plane();
		virtual bool hit(const Ray&, double&, ShadeRec&) const;

	public:
		glm::vec3 point;
		glm::vec3 normal;
		static const double kEpsilon;

};

#endif
