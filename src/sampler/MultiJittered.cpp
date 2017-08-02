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
#include "MultiJittered.h"

MultiJittered::MultiJittered()
	: Sampler() {

}

MultiJittered::MultiJittered(const int numSamples)
	: Sampler(numSamples) {

	GenerateSamples();
}

MultiJittered::MultiJittered(const int numSamples, const int numSets)
	: Sampler(numSamples, numSets) {

	GenerateSamples();
}

void MultiJittered::GenerateSamples() {
	int n = static_cast<int>(sqrt(m_NumSamples));
	float subcell_width = static_cast<float>(1.0 / m_NumSamples);

	glm::vec2 fill_point;
	for (int i = 0; i < m_NumSamples * m_NumSets; i++)
		m_Samples.push_back(fill_point);


	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				m_Samples[j * n + k + i * m_NumSamples].x = (j * n + k) * subcell_width + RandFloat(0.0f, subcell_width);
				m_Samples[j * n + k + i * m_NumSamples].y = (k * n + j) * subcell_width + RandFloat(0.0f, subcell_width);

			}

	// Shuffle X coordinates
	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				int jump = RandInt(k, n - 1);
				float temp = m_Samples[j * n + k + i * m_NumSamples].x;
				m_Samples[j * n + k + i * m_NumSamples].x = m_Samples[j * n + jump + i * m_NumSamples].x;
				m_Samples[j * n + jump + i * m_NumSamples].x = temp;
			}

	// Shuffle Y coordinates
	for (int i = 0; i < m_NumSets; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				int jump = RandInt(k, n - 1);
				float temp = m_Samples[j * n + k + i * m_NumSamples].y;
				m_Samples[j * n + k + i * m_NumSamples].y = m_Samples[j * n + jump + i * m_NumSamples].y;
				m_Samples[j * n + jump + i * m_NumSamples].y = temp;
				
			}
}
