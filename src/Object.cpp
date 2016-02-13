#include "Object.h"

Object::Object()
	: color(BLACK)
{}

Object::Object(const Object &obj)
	: color(obj.color)
{}

Object &Object::operator=(const Object &obj) {
	if (this == &obj)
		return (*this);

	color = obj.color;

	return (*this);
}

Object::~Object()
{}
