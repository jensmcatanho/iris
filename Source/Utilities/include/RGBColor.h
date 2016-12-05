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

/**
 * @addtogroup Utilities
 * @{
 */

/**
 * Handles color channels and operations.
 * @remarks TODO
 */
class RGBColor {
	public:
		/**
		 * Standard constructor.
		 */
		RGBColor();

		/**
		 * Constructs an RGBColor with the target components.
		 * @param new_r Target red component.
		 * @param new_g Target green component.
		 * @param new_b Target blue component.
		 */
		RGBColor(const float new_r, const float new_g, const float new_b);

		/**
		 * Constructs an RGBColor with the target in all components.
		 * @param color Target component.
		 */
		RGBColor(const float color);
		
		/**
		 * Checks if the components of two colors are equal.
		 * @param  rhs Right hand side operand.
		 * @return A boolean value indicating whether the two colors are equal.
		 */
		bool operator==(const RGBColor &rhs) const;

		/**
		 * Adds two colors componentwise.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the componentwise sum of two colors.
		 */
		RGBColor operator+(const RGBColor &rhs) const;

		/**
		 * Substracts two colors componentwise.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the componentwise subtraction of two colors.
		 */
		RGBColor operator-(const RGBColor &rhs) const;

		/**
		 * Multiplies two colors componentwise.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the componentwise multiplication of two colors.
		 */
		RGBColor operator*(const RGBColor &rhs) const;

		/**
		 * Multiplies a color by a number.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the product of a color by a number.
		 */
		RGBColor operator*(const float rhs) const;

		/**
		 * Divides a color by a number.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the division of a color by a number.
		 */
		RGBColor operator/(const float rhs) const;

		/**
		 * Adds two colors componentwise and assigns the result to the left operand.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the componentwise sum of two colors. 
		 */
		RGBColor operator+=(const RGBColor & rhs);

		/**
		 * Substracts two colors componentwise and assigns the result to the left operand.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the componentwise subtraction of two colors.
		 */
		RGBColor operator-=(const RGBColor &rhs);

		/**
		 * Multiplies two colors componentwise and assigns the result to the left operand.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the componentwise multiplication of two colors.
		 */
		RGBColor operator*=(const RGBColor &rhs);

		/**
		 * Multiplies a color by a number and assigns the result to the left operand.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the product of a color by a number.
		 */
		RGBColor operator*=(const float rhs);

		/**
		 * Divides a color by a number and assigns the result to the left operand.
		 * @param  rhs Right hand side operand.
		 * @return The resulting color of the division of a color by a number.
		 */
		RGBColor operator/=(const float rhs);

		/**
		 * Raises the components of the color to a power.
		 * @param  exponent Target power.
		 * @return The resulting color of powering each component of the color by a number.
		 */
		RGBColor Pow(const float exponent) const;

		/**
		 * Returns the average of the components of the color.
		 * @return The resulting average of the components of the color.
		 */
		float Average() const;

		/**
		 * Handles overflow of the color channel by dividing all the components by the out-of-gamut component.
		 * @param  raw_color Out-of-gamut color.
		 * @return The clamped color within the correct range.
		 */
		static RGBColor MaxToOne(const RGBColor &raw_color);

		/**
		 * Handles overflow of the color channel by mapping the out-of-gamut component to a target color.
		 * @param  raw_color    Out-of-gamut color.
		 * @param  target_color Target color.
		 * @return The campled color within the correct range with any overflow mapped to the target color.
		 */
		static RGBColor ClampToColor(const RGBColor &raw_color, const RGBColor &target_color);

		/**
		 * Black color.
		 */
		static const RGBColor Black;

		/**
		 * White color.
		 */
		static const RGBColor White;

		/**
		 * Red color.
		 */
		static const RGBColor Red;

		/**
		 * Green color.
		 */
		static const RGBColor Green;

		/**
		 * Blue color.
		 */
		static const RGBColor Blue;

		/**
		 * Red component.
		 */
		float r;

		/**
		 * Green component.
		 */
		float g;

		/**
		 * Blue component.
		 */
		float b;
};

inline bool RGBColor::operator==(const RGBColor &rhs) const {
	return (r == rhs.r) && (g == rhs.g) && (b == rhs.b);

}

inline RGBColor RGBColor::operator+(const RGBColor &rhs) const {
	return RGBColor(r + rhs.r, g + rhs.g, b + rhs.b);

}

inline RGBColor RGBColor::operator-(const RGBColor &rhs) const {
	return RGBColor(r - rhs.r, g - rhs.g, b - rhs.b);

}

inline RGBColor RGBColor::operator*(const RGBColor &rhs) const {
	return RGBColor(r * rhs.r, g * rhs.g, b * rhs.b);

}

inline RGBColor RGBColor::operator*(const float rhs) const {
	return RGBColor(r * rhs, g * rhs, b * rhs);

}

inline RGBColor RGBColor::operator/(const float rhs) const {
	return RGBColor(r / rhs, g / rhs, b / rhs);

}

inline RGBColor RGBColor::operator+=(const RGBColor &rhs) {
	r += rhs.r;
	g += rhs.g;
	b += rhs.b;

	return (*this);
}

inline RGBColor RGBColor::operator-=(const RGBColor &rhs) {
	r -= rhs.r;
	g -= rhs.g;
	b -= rhs.b;

	return (*this);
}

inline RGBColor RGBColor::operator*=(const float rhs) {
	r *= rhs;
	g *= rhs;
	b *= rhs;

	return (*this);
}

inline RGBColor RGBColor::operator/=(const float rhs) {
	r /= rhs;
	g /= rhs;
	b /= rhs;

	return (*this);
}

inline float RGBColor::Average() const {
	return (float)(0.333333333333f * (r + g + b));

}

/**
 * @}
 */

#endif
