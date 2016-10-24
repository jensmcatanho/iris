#ifndef OBJECT_H
#define OBJECT_H

#include "Constants.h"
#include "Ray.h"
#include "ShadeRecord.h"

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
		RGBColor color;

};

inline void Object::setColor(const float r, const float g, const float b) {
	color.r = r;
	color.g = g;
	color.b = b;
}

inline void Object::setColor(const RGBColor c) {
	color = c;

}

inline RGBColor Object::getColor(void) {
	return (color);
}

#endif
