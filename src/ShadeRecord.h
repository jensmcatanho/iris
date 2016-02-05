#ifndef SHADERECORD_H
#define SHADERECORD_H

#include "RGBColor.h"

class World;

class ShadeRecord {
	public:
		ShadeRec(World&);
		ShadeRec(const ShadeRecord&);

		bool hit;
		glm::vec3 hitPoint;
		glm::vec3 normal;
		RGBColor color;
		World& w;

};

#endif
