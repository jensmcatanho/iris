/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016 Jean Michel Catanho

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
-----------------------------------------------------------------------------
*/
#ifndef PREREQUISITES_H
#define PREREQUISITES_H

// Tracer version related defines.
#define DRACO_MAJOR_VERSION 1
#define DRACO_MINOR_VERSION 0
#define DRACO_PATCH_VERSION 0
#define DRACO_VERSION (DRACO_MAJOR_VERSION << 8) | (DRACO_MINOR_VERSION << 4) | DRACO_PATCH_VERSION

// Forward declarations.
class Ambient;
class BRDF;
class Camera;
class GlossySpecular;
class Hammersley;
class Jittered;
class Lambertian;
class Light;
class LuaState;
class Material;
class Matte;
class MultiJittered;
class MultipleObjects;
class NRooks;
class Object;
class Pinhole;
class Plane;
class PointLight;
class PureRandom;
class Ray;
class RayCast;
class Regular;
class RGBColor;
class Sampler;
class Sphere;
class Surface;
class Tracer;
class ViewPlane;
class World;

// STL
#include "StandardHeaders.h"

// GLM
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

// Lua
extern "C" {
	#include "lua.h"
	#include "lauxlib.h"
	#include "lualib.h"
}

// Draconian
#include "Constants.h"
#include "Logger.h"

#endif