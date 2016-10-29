#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <glm/gtc/constants.hpp>

// Mathematical constants
const float PI = glm::pi<float>();
const float HALF_PI = glm::half_pi<float>();
const float TWO_PI = 2 * glm::pi<float>();

// Intersection constants
const float kEpsilon = 0.0001f;
const float kHugeValue = 1.0E10;

#endif
