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

class Object {
	public:
		// Default constructor.
		Object();

		// Return true and shading information if a ray intersects with this Object.
		virtual bool Hit(const Ray &, double &, ShadeRecord &) const = 0;

		// Return true if a shadow ray intersects with this Object.
		virtual bool ShadowHit(const Ray &, float &) const = 0;

		// Define whether this Object casts shadows over other objects.
		void CastsShadows(bool);

		// Return true if this Object casts shadows over other objects.
		bool CastsShadows() const;

		// Return a pointer to this Object's material.
		std::shared_ptr<Material> GetMaterial() const;

		// Define a material pointer to this Object.
		virtual void SetMaterial(std::shared_ptr<Material>);

	protected:
		// Smart pointer to a Material type.
		std::shared_ptr<Material> m_MaterialPtr;

		// Store information about whether this object casts shadows over other objects.
		bool m_Shadows;

};

inline std::shared_ptr<Material> Object::GetMaterial() const {
	return m_MaterialPtr;
}

inline void Object::CastsShadows(bool flag) {
	m_Shadows = flag;
}

inline bool Object::CastsShadows() const {
	return m_Shadows;
}

#endif
