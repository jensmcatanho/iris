#include "Regular.h"

Regular::Regular()
	: Sampler() {

}

Regular::Regular(const int numSp)
	: Sampler(numSp) {

	generateSamples();
}

Regular::Regular(const Regular &r)
	: Sampler(r) {

	generateSamples();
}

Regular &Regular::operator=(const Regular &r) {
	if (this == &r)
		return (*this);

	Sampler::operator=(r);

	return (*this);
}

Regular *Regular::clone() const {
	return (new Regular(*this));

}

void Regular::generateSamples() {
	int n = (int)sqrt(numSamples);
	int x, y;

	for (int p = 0; p < numSets; p++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++) {
				x = (k + 0.5) / n;
				y = (j + 0.5) / n;

				samples.push_back( glm::vec2(x, y) );
			}
}
