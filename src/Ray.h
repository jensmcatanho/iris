#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>

class Ray {
	public:
		Ray();
		Ray(glm::vec3&, glm::vec3&);
		Ray(const Ray&);
		~Ray();
		Ray& operator=(const Ray&);

	public:
		glm::vec3 origin;
		glm::vec3 direction;

};

#endif
