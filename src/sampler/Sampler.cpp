/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016-2017 Jean Michel Catanho

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

Sampler::Sampler()
	: m_NumSamples(1),
	  m_NumSets(83),
	  m_Count(0),
	  m_Jump(0) {

	m_Samples.reserve(m_NumSets);
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

void Sampler::MapToUnitDisk() {
	int size = m_Samples.size();
	glm::vec2 samplePoint;

	// Polar coordinates.
	double radius;
	double phi;

	m_DiskSamples.reserve(size);

	for (int i = 0; i < size; i++) {
		samplePoint.x = static_cast<float>(2.0 * m_Samples[i].x - 1.0);
		samplePoint.y = static_cast<float>(2.0 * m_Samples[i].y - 1.0);

		if (samplePoint.x > -samplePoint.y) {
			if (samplePoint.x > samplePoint.y) {
				// Sector 1.
				radius = samplePoint.x;
				phi = samplePoint.y / samplePoint.x;

			}
			else {
				// Sector 2.
				radius = samplePoint.y;
				phi = 2.0 - samplePoint.x / samplePoint.y;
			}

		}
		else {
			if (samplePoint.x < samplePoint.y) {
				// Sector 3.
				radius = -samplePoint.x;
				phi = 4.0 + samplePoint.y / samplePoint.x;

			}
			else {
				// Sector 4.
				radius = -samplePoint.y;
				phi = samplePoint.y != 0.0 ? 6.0 - samplePoint.x / samplePoint.y : 0.0;
			}
		}

		phi *= PI / 4.0;
		m_DiskSamples.push_back(glm::vec2(radius * cos(phi), radius * sin(phi)));
	}

	m_Samples.erase(m_Samples.begin(), m_Samples.end());
}

void Sampler::MapToHemisphere(const float e) {
	int size = m_Samples.size();
	m_HemisphereSamples.reserve(size);

	for (int i = 0; i < size; i++) {
		// Phi
		double phi = 2.0 * PI * m_Samples[i].x;
		double cos_phi = glm::cos(phi);
		double sin_phi = glm::sin(phi);

		// Theta
		double cos_theta = glm::pow(1.0 - m_Samples[i].y, 1.0 / (e + 1.0));
		double sin_theta = glm::sqrt(1.0 - cos_theta * cos_theta);  //sin² + cos² = 1

		// Point p
		double pu = sin_theta * cos_phi;
		double pv = sin_theta * sin_phi;
		double pw = cos_theta;

		m_HemisphereSamples.push_back(glm::vec3(pu, pv, pw));
	}
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
	SetJump();

	return m_Samples[m_Jump + m_ShuffledIndices[m_Jump + m_Count++ % m_NumSamples]];
}

glm::vec2 Sampler::SampleUnitDisk() {
	SetJump();

	return m_DiskSamples[m_Jump + m_ShuffledIndices[m_Jump + m_Count++ % m_NumSamples]];
}

glm::vec3 Sampler::SampleHemisphere() {
	SetJump();

	return m_HemisphereSamples[m_Jump + m_ShuffledIndices[m_Jump + m_Count++ % m_NumSamples]];
}

void Sampler::SetJump() {
	if (m_Count % m_NumSamples == 0) {
		m_Jump = (RandInt() % m_NumSets) * m_NumSamples;
		m_Jump = m_Jump >= 0 ? m_Jump : -m_Jump;
	}
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
