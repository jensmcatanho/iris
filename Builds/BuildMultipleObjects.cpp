#include "../src/Sphere.h"
#include "../src/Plane.h"

void World::build() {
	vp.set_hres(200);
	vp.set_vres(200);
	vp.setSampler(new MultiJittered(256));
	vp.set_pixel_size(1.0);
	tracerPtr = new MultipleObjects(this); 
	backgroundColor = RGBColor(0.0f, 0.0f, 0.0f);
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->setCenter(glm::vec3(0.0f, -25.0f, 0.0f));
	sphere_ptr->setRadius(80);
	sphere_ptr->setColor(1, 0, 0);
	addObject(sphere_ptr);
	
	sphere_ptr = new Sphere;
	sphere_ptr->setCenter(glm::vec3(0.0f, 30.0f, 0.0f));
	sphere_ptr->setRadius(60);
	sphere_ptr->setColor(1, 1, 0);
	addObject(sphere_ptr);
	
	Plane* plane_ptr = new Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	plane_ptr->setColor(0.0, 0.3, 0.0);
	addObject(plane_ptr);

}

