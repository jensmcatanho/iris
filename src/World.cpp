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

	deleteObjects();
}

void World::renderScene() const {
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
			displayPixel(r, c, pixelColor);
		}
}

RGBColor World::maxToOne(const RGBColor& raw_color) const {
	float max_value = glm::max(raw_color.r, glm::max(raw_color.g, raw_color.b));
	
	if (max_value > 1.0)
		return RGBColor(raw_color.r/max_value, raw_color.g/max_value, raw_color.b/max_value);
	else
		return (raw_color);

}

RGBColor World::clampToColor(const RGBColor& raw_color, const RGBColor& target_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = target_color.r;
		c.g = target_color.g;
		c.b = target_color.b;
	}
		
	return (c);
}

void World::displayPixel(const int row, const int column, const RGBColor& raw_color) const {
	RGBColor mapped_color;
	RGBColor target_color(1.0f, 0.0f, 0.0f); //To do: Set target color in build member function

	if (vp.show_out_of_gamut)
		mapped_color = clampToColor(raw_color, target_color);
	else
		mapped_color = maxToOne(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = RGBColor(glm::pow(mapped_color.r, vp.inv_gamma),
					glm::pow(mapped_color.g, vp.inv_gamma),
					glm::pow(mapped_color.b, vp.inv_gamma));

	pixels[row * vp.hres + column].r = mapped_color.r;
	pixels[row * vp.hres + column].g = mapped_color.g;
	pixels[row * vp.hres + column].b = mapped_color.b;

}

ShadeRecord World::hitObjects(const Ray& ray) {
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

void World::deleteObjects(void) {
	int num_objects = objects.size();
	
	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}
	
	objects.erase(objects.begin(), objects.end());

}
