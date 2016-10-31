#include "RGBColor.h"

// Color constants
const RGBColor RGBColor::Black(0.0f, 0.0f, 0.0f);
const RGBColor RGBColor::White(1.0f, 1.0f, 1.0f);
const RGBColor RGBColor::Red(1.0f, 0.0f, 0.0f);
const RGBColor RGBColor::Green(0.0f, 1.0f, 0.0f);
const RGBColor RGBColor::Blue(0.0f, 0.0f, 1.0f);

RGBColor::RGBColor()
	: r(0.0f),
	  g(0.0f),
	  b(0.0f) {

}

RGBColor::RGBColor(const double new_r, const double new_g, const double new_b)
	: r(new_r),
	  g(new_g),
	  b(new_b) {

}

RGBColor::RGBColor(const double color)
	: r(color),
	  g(color),
	  b(color) {

}

RGBColor RGBColor::Pow(const float exponent) const {
	return RGBColor(glm::pow(r, exponent), glm::pow(g, exponent), glm::pow(b, exponent));

}
