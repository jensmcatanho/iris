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

void World::Build() {
	m_ViewPlane.SetWidth(200);
	m_ViewPlane.SetHeight(200);

	std::shared_ptr<MultiJittered> newSampler(new MultiJittered(16));
	m_ViewPlane.SetSampler(newSampler);
	m_ViewPlane.SetPixelSize(1.0);

	std::shared_ptr<MultipleObjects> newTracer(new MultipleObjects(shared_from_this()));
	m_TracerPtr = newTracer;
	m_BackgroundColor = RGBColor(0.0f, 0.0f, 0.0f);

	std::shared_ptr<Sphere> sphere_ptr(new Sphere);
	sphere_ptr->SetCenter(glm::vec3(0.0f, 0.0f, 0.0f));
	sphere_ptr->SetRadius(80);
	sphere_ptr->SetColor(0, 1, 0);
	AddObject(sphere_ptr);

	// Back
	std::shared_ptr<Plane> plane_ptr(new Plane(glm::vec3(0.0f, 0.0f, -80.0f), glm::vec3(0.0f, 0.0f, 1.0f)));
	plane_ptr->SetColor(0.1f, 0.1f, 0.1f);
	AddObject(plane_ptr);

	// Top
	std::shared_ptr<Plane> plane_ptr2(new Plane(glm::vec3(0.0f, 80.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.2f)));
	plane_ptr2->SetColor(1.0f, 1.0f, 1.0f);
	AddObject(plane_ptr2);

	// Bottom
	std::shared_ptr<Plane> plane_ptr3(new Plane(glm::vec3(0.0f, -80.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.2f)));
	plane_ptr3->SetColor(1.0f, 1.0f, 1.0f);
	AddObject(plane_ptr3);

	// Left
	std::shared_ptr<Plane> plane_ptr4(new Plane(glm::vec3(-80.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.2f)));
	plane_ptr4->SetColor(1.0f, 0.0f, 0.0f);
	AddObject(plane_ptr4);

	// Right
	std::shared_ptr<Plane> plane_ptr5(new Plane(glm::vec3(80.0f, 0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.2f)));
	plane_ptr5->SetColor(0.0f, 0.0f, 1.0f);
	AddObject(plane_ptr5);
}

#endif