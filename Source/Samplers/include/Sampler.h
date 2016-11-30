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
		/**
		 * Default constructor.
		 */
		Sampler();

		/**
		 * Constructs a Sampler with the passed number of samples.
		 * @param {const int} numSamples Number of samples.
		 */
		Sampler(const int);

		/**
		 * Constructs a Sampler with the passed number of samples and sets.
		 * @param {const int} numSamples Number of samples.
		 * @param {const int} numSets    Number of sets.
		 */
		Sampler(const int, const int);

		/**
		 * Generates sample patterns in a unit square.
		 */
		virtual void GenerateSamples() = 0;
 
		/**
		 * Maps 2D sample points in the unit square to a unit disk.
		 */
		void MapToUnitDisk();

		/**
		 * Maps 2D sample points in the unit square to a hemisphere.
		 * @param {const float} e Controls how the samples are spaced through the hemisphere.
		 */
		void MapToHemisphere(const float);

		/**
		 * Sets up randomly shuffled indices for the samples list.
		 */
		void SetupShuffledIndices();

		/**
		 * Shuffles the X values of the samples list.
		 */
		void ShuffleX();

		/**
		 * Shuffles the Y values of the samples list.
		 */
		void ShuffleY();

		/**
		 * Returns a sample in a unit square with a random jump.
		 * @return glm::vec2
		 */
		glm::vec2 SampleUnitSquare();

		/**
		 * Returns a sample in a unit disk with a random jump.
		 * @return glm::vec2
		 */
		glm::vec2 SampleUnitDisk();

		/**
		 * Returns a sample in a hemisphere with a random jump.
		 * @return glm::vec3
		 */
		glm::vec3 SampleHemisphere();

		/**
		 * Returns the number of samples of the sampler.
		 * @return {int}
		 */
		int GetNumOfSamples() const;
		
	protected:
		/**
		 * Sets the index jump
		 */
		void SetJump();

		/** 
		 * Returns a random integer with no restrictions.
		 * @return {int}
		 */
		int RandInt();

		/**
		 * Returns a random integer within a given range.
		 * @param {const int} min Lower boundary.
		 * @param {const int} max Higher boundary.
		 * @return {int}
		 */
		int RandInt(const int, const int);

		/** 
		 * Returns a random float with no restrictions.
		 * @return {float}
		 */
		float RandFloat();

		/**
		 * Returns a random float within a given range.
		 * @param {const float} min Lower boundary.
		 * @param {const float} max Higher boundary.
		 * @return {float}
		 */
		float RandFloat(const float, const float);

		/**
		 * Number of sample points within a set.
		 * @type {int}
		 */
		int m_NumSamples;

		/**
		 * Number of sample sets.
		 * @type {int}
		 */
		int m_NumSets;

		/**
		 * List of sample points within a unit square.
		 * @type {std::vector<glm::vec2>}
		 */
		std::vector<glm::vec2> m_Samples;

		/**
		 * List of sample points within a unit disk.
		 * @type {std::vector<glm::vec2>}
		 */
		std::vector<glm::vec2> m_DiskSamples;

		/**
		 * List of sample points within a hemisphere.
		 * @type {std::vector<glm::vec3>}
		 */
		std::vector<glm::vec3> m_HemisphereSamples;

	private:
		/**
		 * List of shuffled indices.
		 * @type {std::vector<int>}
		 */
		std::vector<int> m_ShuffledIndices;

		/**
		 * Number of sample points used.
		 * @type {unsigned long}
		 */
		unsigned long m_Count;

		/**
		 * Random jump for indexing the list of samples and the list of indices.
		 * @type {int}
		 */
		int m_Jump;

		/**
		 * Random engine.
		 * @type {std::mt19937}
		 */
		std::mt19937 m_RandEngine;

};

inline int Sampler::GetNumOfSamples() const {
	return m_NumSamples;
}

#endif
