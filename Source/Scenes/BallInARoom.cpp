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