/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016-2017 Jean Michel Catanho

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
#ifndef WORLD_H
#define WORLD_H

#include "Prerequisites.h"
#include "RGBColor.h"
#include "ViewPlane.h"

/**
 * @addtogroup World
 * @{
 */

/**
 * Simplifies notation of a vector of smart pointers to objects.
 */
typedef std::vector<std::shared_ptr<Object>> ObjectList;

/**
 * Simplifies notation of a vector of smart pointers to lights.
 */
typedef std::vector<std::shared_ptr<Light>> LightList;

/**
 * TODO.
 * @remarks TODO.
 */
class World {
	friend class LuaState;

	public:
		/**
		 * Standard constructor.
		 */
		World();

		/**
		 * Checks if an object has been hit by a ray.
		 * @param  ray Ray traced.
		 * @return Information about the surface of the object hit.
		 */
		Surface HitObjects(const Ray &ray);

		/**
		 * Saves color information in a pixel.
		 */
		void DisplayPixel(const int row, const int column, const RGBColor &raw_color) const;

		/**
		 * Sets a camera to the scene.
		 * @param camera New camera.
		 */
		void SetCamera(std::shared_ptr<Camera> camera);

		/**
		 * View plane.
		 */
		ViewPlane m_ViewPlane;

		/**
		 * Background color.
		 */
		RGBColor m_BackgroundColor;

		/**
		 * Scene ambient light.
		 */
		std::shared_ptr<Light> m_AmbientPtr;

		/**
		 * Scene camera.
		 */
		std::shared_ptr<Camera> m_CameraPtr;

		/**
		 * Scene tracer.
		 */
		std::shared_ptr<Tracer> m_TracerPtr;

		/**
		 * List of the pixels in the view plane.
		 */
		RGBColor *m_Pixels;

		/**
		 * List of the objects in the scene.
		 */
		ObjectList m_Objects;

		/**
		 * List of the lights in the scene.
		 */
		LightList m_Lights;


	private:
		/**
		 * Adds an object to the scene.
		 * @param objPtr New object.
		 */
		void AddObject(std::shared_ptr<Object> objPtr);
		
		/**
		 * Adds a light to the scene.
		 * @param lightPtr New light.
		 */
		void AddLight(std::shared_ptr<Light> lightPtr);
};

inline void World::SetCamera(std::shared_ptr<Camera> camera) {
	m_CameraPtr = camera;
}

inline void World::AddObject(std::shared_ptr<Object> objPtr) {
	m_Objects.push_back(objPtr);
}

inline void World::AddLight(std::shared_ptr<Light> lightPtr) {
	m_Lights.push_back(lightPtr);
}

/**
 * @}
 */

#endif
