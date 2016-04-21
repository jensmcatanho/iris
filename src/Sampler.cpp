#include "Sampler.h"

Sampler::Sampler()
	: numSamples(1),
	  numSets(83),
	  count(0),
	  jump(0) {

	samples.reserve(numSets); // No need to multiply here, result already known
	setupShuffledIndices();

}

Sampler::Sampler(const int numSp)
	: numSamples(numSp),
	  numSets(83),
	  count(0),
	  jump(0) {

	samples.reserve(numSamples * numSets);
	setupShuffledIndices();

}

Sampler::Sampler(const int numSp, const int numSt)
	: numSamples(numSp),
	  numSets(numSt),
	  count(0),
	  jump(0) {

	samples.reserve(numSamples * numSets);
	setupShuffledIndices();

}

Sampler::Sampler(const Sampler& sp)
	: numSamples(sp.numSamples),
	  numSets(sp.numSets),
	  samples(sp.samples),
	  shuffledIndices(sp.shuffledIndices),
	  count(sp.count),
	  jump(sp.jump)
{}

Sampler::~Sampler()
{}

Sampler& Sampler::operator=(const Sampler& sp) {
	if (this == &sp)
		return (*this);

	numSamples = sp.numSamples;
	numSets = sp.numSets;
	samples = sp.samples;
	count = sp.count;
	jump = sp.jump;

	return (*this);
}

void Sampler::setupShuffledIndices() {/*
	shuffledIndices.reserve(numSamples * numSets);
	std::vector<int> indices;

	for (int i = 0; i < numSamples; i++)
		indices.push_back(i);

	for (int i = 0; i < numSets; i++) {
		std::random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < numSamples; j++)
			shuffledIndices.push_back(indices[j]);
	}*/
}

void Sampler::shuffleSamples() {
	
}

glm::vec2 Sampler::sampleUnitSquare() {
	//Needs implementation of rand_int()
	//if (count % numSamples == 0)
	//	jump = (rand_int() % numSets) * numSamples;

	return samples[/*jump*/ + count++ % (numSamples * numSets)];

}


int Sampler::getNumSamples() {
	return numSamples;
}

int Sampler::randInt() {
	randEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	return randEngine();
}

float Sampler::randFloat() {
	randEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<float> realDistr(randEngine.min(), randEngine.max());
	return realDistr(randEngine);

}
