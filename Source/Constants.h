#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <glm/gtc/constants.hpp>
#include "RGBColor.h"

// Mathematical constants
const float PI = glm::pi<float>();
const float HALF_PI = glm::half_pi<float>();
const float TWO_PI = 2 * glm::pi<float>();

// Intersection constants
const float kEpsilon = 0.0001f;
const float kHugeValue = 1.0E10;

// Color constants
const RGBColor BLACK(0.0f, 0.0f, 0.0f);
const RGBColor WHITE(1.0f, 1.0f, 1.0f);
const RGBColor RED(1.0f, 0.0f, 0.0f);
const RGBColor GREEN(0.0f, 1.0f, 0.0f);
const RGBColor BLUE(0.0f, 0.0f, 1.0f);

#endif
