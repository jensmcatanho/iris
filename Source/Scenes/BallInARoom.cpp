#if 0

void World::build() {
	vp.setWidth(200);
	vp.setHeight(200);
	vp.setSampler(new MultiJittered(256));
	vp.setPixelSize(1.0);
	tracerPtr = new MultipleObjects(this);
	backgroundColor = RGBColor(0.0f, 0.0f, 0.0f);

	Sphere* sphere_ptr = new Sphere;
	sphere_ptr->setCenter(glm::vec3(0.0f, 0.0f, 0.0f));
	sphere_ptr->setRadius(80);
	sphere_ptr->setColor(0, 1, 0);
	addObject(sphere_ptr);

	// Back
	Plane* plane_ptr = new Plane(glm::vec3(0.0f, 0.0f, -80.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	plane_ptr->setColor(0.1f, 0.1f, 0.1f);
	addObject(plane_ptr);

	// Top
	Plane* plane_ptr2 = new Plane(glm::vec3(0.0f, 80.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.2f));
	plane_ptr2->setColor(1.0f, 1.0f, 1.0f);
	addObject(plane_ptr2);

	// Bottom
	Plane* plane_ptr3 = new Plane(glm::vec3(0.0f, -80.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.2f));
	plane_ptr3->setColor(1.0f, 1.0f, 1.0f);
	addObject(plane_ptr3);

	// Left
	Plane* plane_ptr4 = new Plane(glm::vec3(-80.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.2f));
	plane_ptr4->setColor(1.0f, 0.0f, 0.0f);
	addObject(plane_ptr4);

	// Right
	Plane* plane_ptr5 = new Plane(glm::vec3(80.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.2f));
	plane_ptr5->setColor(0.0f, 0.0f, 1.0f);
	addObject(plane_ptr5);
}

#endif