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
	float subcell_width = 1.0 / static_cast<float>(m_NumSamples);

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
