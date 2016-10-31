#ifndef SHADERECORD_H
#define SHADERECORD_H

// TODO: Check if ShadeRecord needs to be a class instead of a struct.

#include "Prerequisites.h"
#include "RGBColor.h"

class ShadeRecord {
	public:
		ShadeRecord(World &);

		bool m_Hit;
		glm::vec3 m_HitPoint;
		glm::vec3 m_Normal;
		RGBColor m_Color;
		World &w;  // TODO: Check if this reference to World is necessary.
};

#endif
