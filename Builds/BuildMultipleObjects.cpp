#include "../src/Sphere.h"
#include "../src/Plane.h"

void 												
World::build(void) {
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	
	tracerPtr = new MultipleObjects(this); 
	
	backgroundColor = RGBColor(0.0f, 0.0f, 0.0f);
	
	// use access functions to set centre and radius
	
	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->setCenter(glm::vec3(0.0f, -25.0f, 0.0f));
	sphere_ptr->setRadius(80);
	sphere_ptr->setColor(1, 0, 0);  // red
	add_object(sphere_ptr);

	// use constructor to set centre and radius 
	
	sphere_ptr = new Sphere(glm::vec3(0.0f, 30.0f, 0.0f), 60.0f);
	sphere_ptr->setColor(1, 1, 0);	// yellow
	add_object(sphere_ptr);
	
	Plane* plane_ptr = new Plane(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 1.0f));
	plane_ptr->setColor(0.0, 0.3, 0.0);	// dark green
	add_object(plane_ptr);
}

