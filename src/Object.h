#ifndef OBJECT_H
#define OBJECT_H

#include "Ray.h"
#include "ShadeRecord.h"

class Object {
	public:
		Object();
		Object(const Object& obj);
		virtual Object* clone() const = 0;
		virtual ~Object();
		virtual bool hit(const Ray& ray, double& t, ShadeRecord& s) const = 0;
		void setColor(const float r, const float g, const float b);
		void setColor(const RGBColor c);
		RGBColor getColor();

	protected:
		RGBColor color;
		Object& operator=(const Object& obj);

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
