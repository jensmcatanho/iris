#ifndef OBJECT_H
#define OBJECT_H

#include "PreRequisites.h"
#include "RGBColor.h"

class Object {
	public:
		Object();
		Object(const Object &obj);
		Object &operator=(const Object &obj);

		virtual bool hit(const Ray &, double &, ShadeRecord &) const = 0;
		void setColor(const float, const float, const float);
		void setColor(const RGBColor);
		RGBColor getColor();

	protected:
		RGBColor m_Color;

};

inline void Object::setColor(const float r, const float g, const float b) {
	m_Color.r = r;
	m_Color.g = g;
	m_Color.b = b;
}

inline void Object::setColor(const RGBColor c) {
	m_Color = c;

}

inline RGBColor Object::getColor() {
	return (m_Color);
}

#endif
