#ifndef SAMPLER_H
#define SAMPLER_H

#include "Prerequisites.h"

class Sampler {
	public:
		Sampler();
		Sampler(const int);
		Sampler(const int, const int);
		Sampler(const Sampler&);

		Sampler& operator=(const Sampler&);
		virtual Sampler* clone() const = 0;

		virtual void generateSamples() = 0;
		void setupShuffledIndices();
		void shuffle_X();
		void shuffle_Y();
		glm::vec2 sampleUnitSquare();
		int getNumSamples();


	protected:
		int randInt();
		int randInt(const int, const int);
		float randFloat();
		float randFloat(const float, const float);
		
	protected:
		int numSamples;
		int numSets;
		std::vector<glm::vec2> samples;
		std::vector<int> shuffledIndices;
		unsigned long count;
		int jump;

		std::mt19937 randEngine;

};

#endif
