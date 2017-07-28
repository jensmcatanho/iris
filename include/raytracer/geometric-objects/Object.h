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

#include "Prerequisites.h"

/**
 * @addtogroup GeometricObjects
 * @{
 */

/**
 * Holder of data of 3D objects.
 * @remarks TODO.
 */
class Object {
	public:
		/**
		 * Standard constructor.
		 */
		Object();

		/**
		 * Checks if a ray intersects with this object and return it's shading information.
		 * @param  ray  Intersection ray.
		 * @param  tmin TODO.
		 * @param  sr   Information about the surface of the object.
		 * @return True, if the object intersects with the given ray.
		 */
		virtual bool Hit(const Ray &ray, double &tmin, Surface &sr) const = 0;

		/**
		 * Checks if a shadow ray intersects with the object.
		 * @param  ray  Shadow ray.
		 * @param  tmin TODO
		 * @return True, if the object intersects with the given ray.
		 */
		virtual bool ShadowHit(const Ray &ray, float &tmin) const = 0;

		/**
		 * Sets if the object casts shadows over other objects.
		 * @param flag Flag that sets if the object casts shadows.
		 */
		void CastsShadows(bool flag);

		/**
		 * Checks if the object casts shadows over other objects.
		 * @return True, if the object casts shadows.
		 */
		bool CastsShadows() const;

		/**
		 * Gets the material of the object.
		 * @return Smart pointer to the material attached to the object.
		 */
		std::shared_ptr<Material> GetMaterial() const;

		/**
		 * Sets a material to the object.
		 * @param material_ptr Smart pointer to a Material type.
		 */
		virtual void SetMaterial(std::shared_ptr<Material> material_ptr);

	protected:
		/**
		 * Material attached to the object.
		 */
		std::shared_ptr<Material> m_MaterialPtr;
		
		/**
		 * Flag that stores information about whether the object casts shadows over other objects.
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

/**
 * @}
 */

#endif
