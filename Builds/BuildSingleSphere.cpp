void World::build(void) {
	vp.set_hres(200);
	vp.set_vres(200);
	vp.set_pixel_size(1.0);
	vp.set_gamma(1.0);
	
	backgroundColor = RGBColor(1.0f, 1.0f, 1.0f);
	tracerPtr = new MultipleObjects(this); 
	
	Sphere* sphere = new Sphere;
	sphere->setCenter(glm::vec3(0.0f, 0.0f, 0.0f));
	sphere->setRadius(85.0);
	sphere->setColor(0.0f, 0.0f, 1.0f);
	add_object(sphere);

}

