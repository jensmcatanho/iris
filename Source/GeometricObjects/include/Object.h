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
		/**
		 * Default constructor.
		 */
		Object();

		/**
		 * Checks if a ray intersects with this object and return it's shading information.
		 * @param {const Ray &} ray Intersection ray.
		 * @param {float &}     tmin TODO
		 * @return {bool}
		 */
		virtual bool Hit(const Ray &, double &, Surface &) const = 0;

		/**
		 * Checks if a shadow ray intersects with the object.
		 * @param {const Ray &} ray Shadow ray.
		 * @param {float &}     tmin TODO
		 * @return {bool}
		 */
		virtual bool ShadowHit(const Ray &, float &) const = 0;

		/**
		 * Sets if the object casts shadows over other objects.
		 * @param {bool} flag Cast shadows flag.
		 */
		void CastsShadows(bool);

		/**
		 * Checks if the object casts shadows over other objects.
		 * @return {bool}
		 */
		bool CastsShadows() const;

		/**
		 * Gets the material of the object.
		 * @return {std::shared_ptr<Material>}
		 */
		std::shared_ptr<Material> GetMaterial() const;

		/**
		 * Sets a material to the object.
		 * @param {std::shared_ptr<Material>} material_ptr Smart pointer to a Material type.
		 */
		virtual void SetMaterial(std::shared_ptr<Material>);

	protected:
		/**
		 * Material attached to the object.
		 * @type {std::shared_ptr<Material>}
		 */
		std::shared_ptr<Material> m_MaterialPtr;
		
		/**
		 * Flag that stores information about whether the object casts shadows over other objects.
		 * @type {bool}
		 */
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
