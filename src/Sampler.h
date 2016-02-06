#ifndef SAMPLER_H
#define SAMPLER_H

#include <algorithm>
#include <vector>

#include <glm/glm.hpp>

class Sampler {
	public:
		Sampler();
		Sampler(const int);
		Sampler(const int, const int);
		Sampler(const Sampler&);
		virtual ~Sampler();

		Sampler& operator=(const Sampler&);
		virtual Sampler* clone() const = 0;

		virtual void generateSamples() = 0;
		void setupShuffledIndices();
		void shuffleSamples();
		glm::vec2 sampleUnitSquare();
		
	protected:
		int numSamples;
		int numSets;
		std::vector<glm::vec2> samples;
		std::vector<int> shuffledIndices;
		unsigned long count;
		int jump;
};

#endif
