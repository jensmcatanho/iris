#include "Object.h"

Object::Object()
	: m_Color(RGBColor::Black) {

}

Object::Object(const Object &obj)
	: m_Color(obj.m_Color) {

}

Object &Object::operator=(const Object &obj) {
	if (this == &obj)
		return (*this);

	m_Color = obj.m_Color;

	return (*this);
}
