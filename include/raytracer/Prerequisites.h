/*
-----------------------------------------------------------------------------
The MIT License (MIT)

Copyright (c) 2016-2017 Jean Michel Catanho

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

#include "Platform.h"

/**
 * Forward declarations.
 */

/**
 * BRDF
 */
class BlinnPhong;
class BRDF;
class Lambertian;
class Phong;

/**
* Camera
*/
class Camera;
class Orthographic;
class Pinhole;
class ThinLens;

/**
* Geometric Objects
*/
class Object;
class Plane;
class Sphere;

/**
* Lights
*/
class Ambient;
class Directional;
class Light;
class PointLight;

/**
* Lua
*/
class LuaState;

/**
* Materials
*/
class Material;
class Matte;
class Plastic;

/**
* Samplers
*/
class Hammersley;
class Jittered;
class MultiJittered;
class NRooks;
class PureRandom;
class Regular;
class Sampler;

/**
* Tracers
*/
class MultipleObjects;
class RayCast;
class Tracer;

/**
* Utilities
*/
class Ray;
class RGBColor;
class Surface;

/**
* Scene
*/
class ProjectionPlane;
class Scene;

/**
* Other
*/
class Core;

/**
* Includes.
*/

/**
* Standard C and C++ Headers
*/
#include "StandardHeaders.h"

/**
* FreeImage
*/
#if IRIS_ARCHITECTURE_TYPE == IRIS_ARCHITECTURE_32
#include "FreeImage/x86/FreeImage.h"
#else
#include "FreeImage/x64/FreeImage.h"
#endif

/**
* GLM
*/
#include <glm/glm.hpp>
#include <glm/gtc/random.hpp>

/**
* Lua
*/
#if IRIS_ARCHITECTURE_TYPE == IRIS_ARCHITECTURE_32
extern "C" {
	#include "lua/x86/lua.h"
	#include "lua/x86/lauxlib.h"
	#include "lua/x86/lualib.h"
}
#else
extern "C" {
	#include "lua/x64/lua.h"
	#include "lua/x64/lauxlib.h"
	#include "lua/x64/lualib.h"
}
#endif

/**
* Iris
*/
#include "Constants.h"
#include "Logger.h"

#endif