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
#ifndef SAMPLER_H
#define SAMPLER_H

#include "Prerequisites.h"

class Sampler {
	public:
		Sampler();

		// Constructs a Sampler with the passed number of samples.
		Sampler(const int);

		// Constructs a Sampler with the passed number of samples and sets.
		Sampler(const int, const int);

		// Generate samples patterns in a unit square.
		virtual void GenerateSamples() = 0;

		// Sets up randomly shuffled indices for the samples array.
		void SetupShuffledIndices();

		// Shuffle the X values of the Samples.
		void ShuffleX();

		// Shuffle the Y values of the Samples.
		void ShuffleY();

		// Returns shuffled values in a unit square with a random jump.
		glm::vec2 SampleUnitSquare();

		inline int GetNumOfSamples() const;
		
	protected:
		// Returns a random integer.
		int RandInt();

		// Returns a random integer within a range.
		int RandInt(const int, const int);

		// Returns a random float.
		float RandFloat();

		// Returns a random float within a range.
		float RandFloat(const float, const float);

		// Number of sample points in a set.
		int m_NumSamples;

		// Number of sample sets.
		int m_NumSets;

		// Sample points in a unit square.
		std::vector<glm::vec2> m_Samples;

	private:
		// Shuffled array of indices.
		std::vector<int> m_ShuffledIndices;

		// Number of sample points used.
		unsigned long m_Count;

		// Random index jump.
		int m_Jump;

		// Random generator.
		std::mt19937 m_RandEngine;

};

inline int Sampler::GetNumOfSamples() const {
	return m_NumSamples;
}

#endif
