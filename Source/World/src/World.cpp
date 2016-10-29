#include "World.h"

#include "MultiJittered.h"
#include "MultipleObjects.h"
#include "Plane.h"
#include "Ray.h"
#include "ShadeRecord.h"
#include "Sphere.h"

void World::build() {
	vp.setWidth(200);
	vp.setHeight(200);
	vp.setSampler(new MultiJittered(256));
	vp.setPixelSize(1.0);
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
	plane_ptr->setColor(0.0f, 0.3f, 0.0f);
	addObject(plane_ptr);

}

World::World()
	: backgroundColor(RGBColor::Black),
	  tracerPtr(nullptr) {

	pixels = new RGBColor[vp.width * vp.height];
}

World::~World() {
	if (tracerPtr) {
		delete tracerPtr;
		tracerPtr = nullptr;
	}

	deleteObjects();
}

void World::renderScene() const {
	RGBColor pixelColor;
	Ray ray;
	float zw = 100.0f;
	glm::vec2 samplePoint;
	ray.direction = glm::vec3(0.0f, 0.0f, -1.0f);

	for (int r = 0; r < vp.height; r++)
		for (int c = 0; c <= vp.width; c++) {
			pixelColor = RGBColor::Black;

			for (int i = 0; i < vp.numSamples; i++) {
				samplePoint = vp.samplerPtr->sampleUnitSquare();
				ray.origin = glm::vec3(vp.pixel_size * (c - 0.5 * vp.width + samplePoint.x), vp.pixel_size * (r - 0.5 * vp.height + samplePoint.y), zw);
				pixelColor += tracerPtr->trace_ray(ray);
				
			}
			
			pixelColor.r /= vp.numSamples;
			pixelColor.g /= vp.numSamples;
			pixelColor.b /= vp.numSamples;
			displayPixel(r, c, pixelColor);
		}
}

void World::displayPixel(const int row, const int column, const RGBColor &raw_color) const {
	RGBColor mapped_color;
	RGBColor target_color(1.0f, 0.0f, 0.0f); //TODO: Set target color in build member function

	if (vp.out_of_gamut)
		mapped_color = clampToColor(raw_color, target_color);
	else
		mapped_color = maxToOne(raw_color);
	
	if (vp.gamma != 1.0)
		mapped_color = RGBColor(glm::pow(mapped_color.r, vp.inv_gamma),
					glm::pow(mapped_color.g, vp.inv_gamma),
					glm::pow(mapped_color.b, vp.inv_gamma));

	pixels[row * vp.width + column].r = mapped_color.r;
	pixels[row * vp.width + column].g = mapped_color.g;
	pixels[row * vp.width + column].b = mapped_color.b;
}

ShadeRecord World::hitObjects(const Ray &ray) {
	ShadeRecord sr(*this); 
	double t; 			
	double tmin = 1000000;
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
		objects[j] = nullptr;
	}
	
	objects.erase(objects.begin(), objects.end());
}

RGBColor World::maxToOne(const RGBColor &raw_color) const {
	float max_value = (float)glm::max(raw_color.r, glm::max(raw_color.g, raw_color.b));
	
	if (max_value > 1.0)
		return RGBColor(raw_color.r/max_value, raw_color.g/max_value, raw_color.b/max_value);
	else
		return (raw_color);
}

RGBColor World::clampToColor(const RGBColor &raw_color, const RGBColor &target_color) const {
	RGBColor c(raw_color);
	
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = target_color.r;
		c.g = target_color.g;
		c.b = target_color.b;
	}
		
	return (c);
}
