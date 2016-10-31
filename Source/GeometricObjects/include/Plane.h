#ifndef PLANE_H
#define PLANE_H

#include "Object.h"

class Plane : public Object {
	public:
		Plane();
		Plane(const glm::vec3 &point, const glm::vec3 &normal);

		// Check if a ray intersects with this Object and returns it's shading information.
		virtual bool Hit(const Ray &, double &, ShadeRecord &) const;
		
	public:
		glm::vec3 m_Point;
		glm::vec3 m_Normal;

};

#endif
