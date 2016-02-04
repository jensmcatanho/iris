#ifndef SHADEREC_H
#define SHADEREC_H

#include "RGBColor.h"

class World;

class ShadeRec {
	public:
		bool hit;
		glm::vec3 hitPoint;
		glm::vec3 normal;
		RGBColor color;
		World& w;

		ShadeRec(World&);

		ShadeRec(const ShadeRec&);

};

#endif
