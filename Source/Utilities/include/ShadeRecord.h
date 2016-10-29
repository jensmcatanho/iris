#ifndef SHADERECORD_H
#define SHADERECORD_H

#include "Prerequisites.h"
#include "RGBColor.h"

class ShadeRecord {
	public:
		ShadeRecord(World &);
		ShadeRecord(const ShadeRecord &);

		bool hit;
		glm::vec3 hitPoint;
		glm::vec3 normal;
		RGBColor color;
		World &w;
};

#endif
