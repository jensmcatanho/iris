#ifndef RAY_H
#define RAY_H

#include "Prerequisites.h"

class Ray {
	public:
		Ray();
		Ray(glm::vec3 &, glm::vec3 &);

		glm::vec3 m_Origin;
		glm::vec3 m_Direction;
};

#endif
