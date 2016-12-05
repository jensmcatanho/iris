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
#include "RGBColor.h"

// Color constants
const RGBColor RGBColor::Black(0.0f, 0.0f, 0.0f);
const RGBColor RGBColor::White(1.0f, 1.0f, 1.0f);
const RGBColor RGBColor::Red(1.0f, 0.0f, 0.0f);
const RGBColor RGBColor::Green(0.0f, 1.0f, 0.0f);
const RGBColor RGBColor::Blue(0.0f, 0.0f, 1.0f);

RGBColor::RGBColor() :
	r(0.0f),
	g(0.0f),
	b(0.0f) {

}

RGBColor::RGBColor(const float new_r, const float new_g, const float new_b) :
	r(new_r),
	g(new_g),
	b(new_b) {

}

RGBColor::RGBColor(const float color) :
	r(color),
	g(color),
	b(color) {

}

RGBColor RGBColor::Pow(const float exponent) const {
	return RGBColor(glm::pow(r, exponent), glm::pow(g, exponent), glm::pow(b, exponent));

}

RGBColor RGBColor::MaxToOne(const RGBColor &raw_color) {
	float max_value = static_cast<float>(glm::max(raw_color.r, glm::max(raw_color.g, raw_color.b)));

	if (max_value > 1.0)
		return raw_color / max_value;
	else
		return raw_color;
}

RGBColor RGBColor::ClampToColor(const RGBColor &raw_color, const RGBColor &target_color) {
	RGBColor clamped_color(raw_color);

	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		clamped_color.r = target_color.r;
		clamped_color.g = target_color.g;
		clamped_color.b = target_color.b;
	}

	return clamped_color;
}