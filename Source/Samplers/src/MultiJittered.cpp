#include "MultiJittered.h"

MultiJittered::MultiJittered()
	: Sampler() {

}

MultiJittered::MultiJittered(const int numSp)
	: Sampler(numSp) {

	generateSamples();
}

MultiJittered::MultiJittered(const int numSp, const int numSt)
	: Sampler(numSp, numSt) {

	generateSamples();
}

MultiJittered::MultiJittered(const MultiJittered &mj)
	: Sampler(mj) {

	generateSamples();
}

MultiJittered &MultiJittered::operator=(const MultiJittered &mj) {
	if (this == &mj)
		return (*this);

	Sampler::operator=(mj);

	return (*this);
}

MultiJittered *MultiJittered::clone() const {
	return (new MultiJittered(*this));

}

void MultiJittered::generateSamples() {
	int n = (int)sqrt(numSamples);
	float subcell_width = 1.0 / (float)numSamples;

	glm::vec2 fill_point;
	for (int i = 0; i < numSamples * numSets; i++)
		samples.push_back(fill_point);


	for (int i = 0; i < numSets; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				samples[j * n + k + i * numSamples].x = (j * n + k) * subcell_width + randFloat(0.0f, subcell_width);
				samples[j * n + k + i * numSamples].y = (k * n + j) * subcell_width + randFloat(0.0f, subcell_width);

			}

	// Shuffle X coordinates
	for (int i = 0; i < numSets; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				int jump = randInt(k, n - 1);
				float temp = samples[j * n + k + i * numSamples].x;
				samples[j * n + k + i * numSamples].x = samples[j * n + jump + i * numSamples].x;
				samples[j * n + jump + i * numSamples].x = temp;
			}

	// Shuffle Y coordinates
	for (int i = 0; i < numSets; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				int jump = randInt(k, n - 1);
				float temp = samples[j * n + k + i * numSamples].y;
				samples[j * n + k + i * numSamples].y = samples[j * n + jump + i * numSamples].y;
				samples[j * n + jump + i * numSamples].y = temp;
				
			}
}
