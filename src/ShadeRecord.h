#ifndef SHADERECORD_H
#define SHADERECORD_H

#include "Constants.h"
#include "RGBColor.h"

class World;

class ShadeRecord {
	public:
		ShadeRecord(World &);
		ShadeRecord(const ShadeRecord &);
		~ShadeRecord();

		bool hit;
		glm::vec3 hitPoint;
		glm::vec3 normal;
		RGBColor color;
		World &w;

};

#endif
