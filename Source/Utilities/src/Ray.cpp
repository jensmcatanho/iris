#include "Ray.h"

Ray::Ray()
	: m_Origin(0.0f, 0.0f, 0.0f), 
	  m_Direction(0.0f, 0.0f, -1.0f) {

}

Ray::Ray(glm::vec3 &origin, glm::vec3 &direction)
	: m_Origin(origin),
	  m_Direction(direction) {

}
