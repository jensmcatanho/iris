/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016 Jean Michel Catanho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef OBJECT_H
#define OBJECT_H

#include "PreRequisites.h"
#include "RGBColor.h"

class Object {
	public:
		Object();

		// Check if a ray intersects with this Object and returns it's shading information.
		virtual bool Hit(const Ray &, double &, ShadeRecord &) const = 0;

		// Check if a shadow ray intersects with this Object.
		virtual bool ShadowHit(const Ray &, float &) const = 0;

		void SetColor(const float, const float, const float);

		void SetColor(const RGBColor);

		RGBColor GetColor() const;

		std::shared_ptr<Material> GetMaterial() const;

		virtual void SetMaterial(std::shared_ptr<Material>);

	protected:
		// Color of the object.
		RGBColor m_Color;

		// Material of the object.
		std::shared_ptr<Material> m_MaterialPtr;

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

inline std::shared_ptr<Material> Object::GetMaterial() const {
	return m_MaterialPtr;
}

#endif
