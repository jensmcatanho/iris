#ifndef WORLD_H
#define WORLD_H

#include "Prerequisites.h"
#include "RGBColor.h"
#include "ViewPlane.h"

class World {
	public:
		ViewPlane vp;
		RGBColor backgroundColor;
		Tracer *tracerPtr;
		std::vector<Object *> objects;
		RGBColor *pixels;

	public:
		World();
		~World();

		void build();
		void renderScene() const;
		void displayPixel(const int, const int, const RGBColor &) const;
		
		ShadeRecord hitObjects(const Ray &);
		void addObject(Object *);

		RGBColor maxToOne(const RGBColor &) const;
		RGBColor clampToColor(const RGBColor &, const RGBColor &) const;

	private:
		void deleteObjects();

};

inline void World::addObject(Object *objPtr) {
	objects.push_back(objPtr);

}

#endif
