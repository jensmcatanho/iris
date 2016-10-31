#ifndef OBJECT_H
#define OBJECT_H

#include "PreRequisites.h"
#include "RGBColor.h"

class Object {
	public:
		Object();

		// Check if a ray intersects with this Object and returns it's shading information.
		virtual bool Hit(const Ray &, double &, ShadeRecord &) const = 0;

		void SetColor(const float, const float, const float);

		void SetColor(const RGBColor);

		RGBColor GetColor() const;

	protected:
		// Color of the object.
		RGBColor m_Color;

};

inline void Object::SetColor(const float r, const float g, const float b) {
	m_Color.r = r;
	m_Color.g = g;
	m_Color.b = b;
}

inline void Object::SetColor(const RGBColor color) {
	m_Color = color;

}

inline RGBColor Object::GetColor() const {
	return (m_Color);
}

#endif
