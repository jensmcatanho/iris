#include "RGBColor.h"

RGBColor::RGBColor()
	: r(0.0f),
	  g(0.0f),
	  b(0.0f)
{}

RGBColor::RGBColor(const double new_r, const double new_g, const double new_b)
	: r(new_r),
	  g(new_g),
	  b(new_b)
{}

RGBColor::RGBColor(const double color)
	: r(color),
	  g(color),
	  b(color)
{}

RGBColor::RGBColor(const RGBColor& color)
	: r(color.r),
	  g(color.g),
	  b(color.b)
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

RGBColor RGBColor::pow(const float exponent) const {
	return RGBColor(glm::pow(r, exponent), glm::pow(g, exponent), glm::pow(b, exponent));

}
