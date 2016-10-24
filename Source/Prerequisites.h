#ifndef PREREQUISITES_H
#define PREREQUISITES_H

// Tracer version related defines.
#define DRACO_MAJOR_VERSION 1
#define DRACO_MINOR_VERSION 0
#define DRACO_PATCH_VERSION 0
#define DRACO_VERSION (DRACO_MAJOR_VERSION << 8) | (DRACO_MINOR_VERSION << 4) | DRACO_PATCH_VERSION

// Forward declarations.
class Hammersley;
class Jittered;
class MultiJittered;
class MultipleObjects;
class NRooks;
class Object;
class Plane;
class PureRandom;
class Ray;
class Regular;
class RGBColor;
class Sampler;
class ShadeRecord;
class Sphere;
class Tracer;
class ViewPlane;
class World;

#include "StandardHeaders.h"
#include "Constants.h"

#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

#endif