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
#ifndef RGBCOLOR_H
#define RGBCOLOR_H

#include "Prerequisites.h"

class RGBColor {
	public:
		RGBColor();
		RGBColor(const double, const double, const double);
		RGBColor(const double);
		
		bool operator==(const RGBColor &) const;

		RGBColor operator+(const RGBColor &) const;
		RGBColor operator-(const RGBColor &) const;
		RGBColor operator*(const RGBColor &) const;
		RGBColor operator*(const float) const;
		RGBColor operator/(const float) const;

		RGBColor operator+=(const RGBColor &);
		RGBColor operator-=(const RGBColor &);
		RGBColor operator*=(const float);
		RGBColor operator/=(const float);

		RGBColor Pow(const float) const;
		float Average() const;

		double r;
		double g; 
		double b;

		// Color constants
		static const RGBColor Black;
		static const RGBColor White;
		static const RGBColor Red;
		static const RGBColor Green;
		static const RGBColor Blue;
};

inline bool RGBColor::operator==(const RGBColor &c) const {
	return (r == c.r) && (g == c.g) && (b == c.b);

}

inline RGBColor RGBColor::operator+(const RGBColor &c) const {
	return RGBColor(r + c.r, g + c.g, b + c.b);

}

inline RGBColor RGBColor::operator-(const RGBColor &c) const {
	return RGBColor(r - c.r, g - c.g, b - c.b);

}

inline RGBColor RGBColor::operator*(const RGBColor &c) const {
	return RGBColor(r * c.r, g * c.g, b * c.b);

}

inline RGBColor RGBColor::operator*(const float f) const {
	return RGBColor(r * f, g * f, b * f);

}

inline RGBColor RGBColor::operator/(const float f) const {
	return RGBColor(r/f, g/f, b/f);

}

inline RGBColor RGBColor::operator+=(const RGBColor &c) {
	r += c.r;
	g += c.g;
	b += c.b;

	return (*this);
}

inline RGBColor RGBColor::operator-=(const RGBColor &c) {
	r -= c.r;
	g -= c.g;
	b -= c.b;

	return (*this);
}

inline RGBColor RGBColor::operator*=(const float f) {
	r *= f;
	g *= f;
	b *= f;

	return (*this);
}

inline RGBColor RGBColor::operator/=(const float f) {
	r /= f;
	g /= f;
	b /= f;

	return (*this);
}

inline float RGBColor::Average() const {
	return (float)(0.333333333333f * (r + g + b));

}

#endif
