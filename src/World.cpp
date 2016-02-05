#include "World.h"
#include "MultipleObjects.h"

//#include "BuildSingleSphere.cpp"
#include "../Builds/BuildMultipleObjects.cpp"

World::World()
	: backgroundColor(0.0f, 0.0f, 0.0f),
	  tracerPtr(NULL) {
	pixels = new RGBColor[vp.hres * vp.vres];

}

World::~World() {
	if (tracerPtr) {
		delete tracerPtr;
		tracerPtr = NULL;
	}

	delete_objects();
}

void World::render_scene() const {
	RGBColor pixelColor;
	Ray ray;
	int hres = vp.hres;
	int vres = vp.vres;
	float s = vp.s;
	float zw = 100.0f;

	ray.direction = glm::vec3(0.0f, 0.0f, -1.0f);

	for (int r = 0; r < vres; r++)
		for (int c = 0; c <= hres; c++) {
			ray.origin = glm::vec3(s * (c - hres/2.0 + 0.5), s * (r - vres/2.0 + 0.5), zw);
			pixelColor = tracerPtr->trace_ray(ray);
			display_pixel(r, c, pixelColor);
		}
}

RGBColor World::max_to_one(const RGBColor& c) const {
	float max_value = max(c.r, max(c.g, c.b));
	
	if (max_value > 1.0)
		return RGBColor(c.r/max_value, c.g/max_value, c.b/max_value);
	else
		return (c);

}

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}
		
	return (c);
}

void
World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;

	if (vp.show_out_of_gamut)
		mapped_color = clamp_to_color(raw_color);
	else
		mapped_color = max_to_one(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = RGBColor(glm::pow(mapped_color.r, vp.inv_gamma), glm::pow(mapped_color.g, vp.inv_gamma), glm::pow(mapped_color.b, vp.inv_gamma));
	
   //have to start from max y coordinate to convert to screen coordinates
   //int x = column;
   //int y = vp.vres - row - 1;

   pixels[column * vp.hres + row].r = mapped_color.r;
   pixels[column * vp.hres + row].g = mapped_color.g;
   pixels[column * vp.hres + row].b = mapped_color.b;

  // paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
  //                           (int)(mapped_color.g * 255),
  //                           (int)(mapped_color.b * 255));
}

ShadeRecord World::hit_objects(const Ray& ray) {
	ShadeRecord sr(*this); 
	double t; 			
	float tmin = 1000000;
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit =  true;
			tmin = t;
			sr.color = objects[j]->getColor();
		}
		
	return (sr);
}

void
World::delete_objects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}	
	
	objects.erase (objects.begin(), objects.end());
}
