#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "ViewPlane.h"
#include "RGBColor.h"
#include "Object.h"

class Tracer;

using namespace std;

class World {
	public:
		ViewPlane vp;
		RGBColor backgroundColor;
		Tracer* tracerPtr;
		vector<Object*> objects;
		RGBColor *pixels;

		World();
		~World();
		void add_object(Object*);
		void build();
		void render_scene() const;
		RGBColor max_to_one(const RGBColor&) const;
		RGBColor clamp_to_color(const RGBColor&) const;
		void display_pixel(const int, const int, const RGBColor&) const;
		ShadeRecord hit_objects(const Ray&);

	private:
		void delete_objects();

};

inline void World::add_object(Object* objPtr) {  
	objects.push_back(objPtr);	
}

#endif
