#include "RGBColor.h"

RGBColor::RGBColor()
	: r(0.0f),
	  g(0.0f),
	  b(0.0f)
{}

RGBColor::RGBColor(const double n_r, const double n_g, const double n_b)
	: r(n_r),
	  g(n_g),
	  b(n_b)
{}

RGBColor::RGBColor(const double rgb)
	: r(rgb),
	  g(rgb),
	  b(rgb)
{}

RGBColor::RGBColor(const RGBColor& c)
	: r(c.r),
	  g(c.g),
	  b(c.b)
{}

RGBColor::~RGBColor()
{}

RGBColor& RGBColor::operator=(const RGBColor& color) {
	if (this == &color)
		return (*this);

	r = color.r;
	g = color.g;
	b = color.b;

	return (*this);
}

RGBColor RGBColor::pow(const float f) const {
	return RGBColor(glm::pow(r, f), glm::pow(g, f), glm::pow(b, f));

}
