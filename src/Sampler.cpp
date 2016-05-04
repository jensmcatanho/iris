#include "Sampler.h"

#include <iostream>

using namespace std;

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

void Sampler::setupShuffledIndices() {
	shuffledIndices.reserve(numSamples * numSets);
	std::vector<int> indices;

	for (int i = 0; i < numSamples; i++)
		indices.push_back(i);

	for (int i = 0; i < numSets; i++) {
		std::random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < numSamples; j++)
			shuffledIndices.push_back(indices[j]);
	}
}

void Sampler::shuffle_X() {
	for (int i = 0; i < numSets; i++)
		for (int j = 0; j < numSamples - 1; j++) {
			int target = randInt() % numSamples + i * numSamples;
			target = target >= 0 ? target : -target;
			float temp = samples[j + i * numSamples + 1].x;
			samples[j + i * numSamples + 1].x = samples[target].x;
			samples[target].x = temp;
		}
}

void Sampler::shuffle_Y() {
	for (int i = 0; i < numSets; i++)
		for (int j = 0; j < numSamples - 1; j++) {
			int target = randInt() % numSamples + i * numSamples;
			target = target >= 0 ? target : -target;
			float temp = samples[j + i * numSamples + 1].y;
			samples[j + i * numSamples + 1].x = samples[target].y;
			samples[target].y = temp;
		}
}

glm::vec2 Sampler::sampleUnitSquare() {
	if (count % numSamples == 0) {
		jump = (randInt() % numSets) * numSamples;
		jump = jump >= 0 ? jump : -jump;

	}

	return samples[jump + shuffledIndices[jump + count++ % numSamples]];

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

int Sampler::randInt(const int min, const int max) {
	randEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_int_distribution<int> intDistr(min, max);
	return intDistr(randEngine);
}

float Sampler::randFloat(const float min, const float max) {
	randEngine.seed(std::chrono::steady_clock::now().time_since_epoch().count());
	std::uniform_real_distribution<float> realDistr(min, max);
	return realDistr(randEngine);

}
