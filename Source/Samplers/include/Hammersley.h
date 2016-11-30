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
#ifndef HAMMERSLEY_H
#define HAMMERSLEY_H

#include "Sampler.h"

class Hammersley : public Sampler {
	public:
		/**
		 * Default constructor.
		 */
		Hammersley();

		/**
		 * Constructs a Sampler with the passed number of samples.
		 * @param {const int} numSamples Number of samples.
		 */
		Hammersley(const int);

		/**
		 * Constructs a Sampler with the passed number of samples and sets.
		 * @param {const int} numSamples Number of samples.
		 * @param {const int} numSets    Number of sets.
		 */
		Hammersley(const int, const int);

	private:
		/**
		 * Generates sample patterns in a unit square.
		 */
		virtual void GenerateSamples();

		/**
		 * Radical-inverse function of an integer in base 2.
		 * @param {int} j TODO
		 * @return {double}
		 */
		double Phi(int) const;
};

#endif
