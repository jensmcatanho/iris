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
#include "Sampler.h"

#include <iostream>

using namespace std;

Sampler::Sampler()
	: m_NumSamples(1),
	  m_NumSets(83),
	  m_Count(0),
	  m_Jump(0) {

	m_Samples.reserve(m_NumSets);  // No need to multiply here, result already known.
	SetupShuffledIndices();
}

Sampler::Sampler(const int numSamples)
	: m_NumSamples(numSamples),
	  m_NumSets(83),
	  m_Count(0),
	  m_Jump(0) {

	m_Samples.reserve(m_NumSamples * m_NumSets);
	SetupShuffledIndices();
}

Sampler::Sampler(const int numSamples, const int numSets)
	: m_NumSamples(numSamples),
	  m_NumSets(numSets),
	  m_Count(0),
	  m_Jump(0) {

	m_Samples.reserve(m_NumSamples * m_NumSets);
	SetupShuffledIndices();
}

void Sampler::SetupShuffledIndices() {
	m_ShuffledIndices.reserve(m_NumSamples * m_NumSets);
	std::vector<int> indices;

	for (int i = 0; i < m_NumSamples; i++)
		indices.push_back(i);

	for (int i = 0; i < m_NumSets; i++) {
		std::random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < m_NumSamples; j++)
			m_ShuffledIndices.push_back(indices[j]);
	}
}

void Sampler::ShuffleX() {
	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < m_NumSamples - 1; j++) {
			int target = RandInt() % m_NumSamples + i * m_NumSamples;
			target = target >= 0 ? target : -target;

			float temp = m_Samples[j + i * m_NumSamples + 1].x;
			m_Samples[j + i * m_NumSamples + 1].x = m_Samples[target].x;
			m_Samples[target].x = temp;
		}
}

void Sampler::ShuffleY() {
	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < m_NumSamples - 1; j++) {
			int target = RandInt() % m_NumSamples + i * m_NumSamples;
			target = target >= 0 ? target : -target;

			float temp = m_Samples[j + i * m_NumSamples + 1].y;
			m_Samples[j + i * m_NumSamples + 1].x = m_Samples[target].y;
			m_Samples[target].y = temp;
		}
}

glm::vec2 Sampler::SampleUnitSquare() {
	if (m_Count % m_NumSamples == 0) {
		m_Jump = (RandInt() % m_NumSets) * m_NumSamples;
		m_Jump = m_Jump >= 0 ? m_Jump : -m_Jump;

	}

	return m_Samples[m_Jump + m_ShuffledIndices[m_Jump + m_Count++ % m_NumSamples]];
}

int Sampler::RandInt() {
	m_RandEngine.seed((unsigned long)std::chrono::steady_clock::now().time_since_epoch().count());

	return m_RandEngine();
}

float Sampler::RandFloat() {
	m_RandEngine.seed((unsigned long)std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<float> realDistr((float)m_RandEngine.min(), (float)m_RandEngine.max());

	return realDistr(m_RandEngine);
}

int Sampler::RandInt(const int min, const int max) {
	m_RandEngine.seed((unsigned long)std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> intDistr(min, max);

	return intDistr(m_RandEngine);
}

float Sampler::RandFloat(const float min, const float max) {
	m_RandEngine.seed((unsigned long)std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<float> realDistr(min, max);

	return realDistr(m_RandEngine);
}
