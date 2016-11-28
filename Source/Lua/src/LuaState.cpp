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
#include "LuaState.h"

// Cameras
#include "Pinhole.h"

// Geometric Objects
#include "Sphere.h"
#include "Plane.h"

// Lights
#include "Ambient.h"
#include "Directional.h"
#include "PointLight.h"

// Materials
#include "Matte.h"
#include "Phong.h"

// Samplers
#include "Hammersley.h"
#include "Jittered.h"
#include "MultiJittered.h"
#include "NRooks.h"
#include "PureRandom.h"
#include "Regular.h"

// Tracers
#include "MultipleObjects.h"
#include "RayCast.h"

// World
#include "ViewPlane.h"
#include "World.h"

LuaState::LuaState(std::shared_ptr<World> world_ptr) :
	m_L(nullptr),
	m_WorldPtr(world_ptr) {

	m_L = luaL_newstate();
	luaL_openlibs(m_L);
}

LuaState::~LuaState() {
	m_L = nullptr;
}

bool LuaState::Start(const std::string &filename) {
	if (luaL_loadfile(m_L, filename.c_str()) != LUA_OK) {
		Logger::ErrorLog(lua_tostring(m_L, -1), "LuaState::Load()");
		return false;
	}

	if (lua_pcall(m_L, 0, LUA_MULTRET, 0) == LUA_OK)
		return true;

	Logger::ErrorLog(lua_tostring(m_L, -1), "LuaState::Load()");

	return false;
}

void LuaState::LoadScene() {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);

	lua_getglobal(m_L, "scene");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	std::shared_ptr<Ambient> ambient_ptr(new Ambient);
	worldPtr->m_AmbientPtr = ambient_ptr;

	ParseImage();
	ParseTracer();
	ParseCamera();
	ParseLights();
	ParseObjects();

	lua_pop(m_L, 1);
}

void LuaState::ParseImage() {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);

	lua_getfield(m_L, -1, "image");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	lua_getfield(m_L, -1, "width");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	worldPtr->m_ViewPlane.SetWidth(static_cast<int>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "height");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	worldPtr->m_ViewPlane.SetHeight(static_cast<int>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "pixel_size");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	worldPtr->m_ViewPlane.SetPixelSize(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "background_color");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	worldPtr->m_BackgroundColor = ParseColor();
	lua_pop(m_L, 1);

	ParseSampler();
	lua_pop(m_L, 1);
}

void LuaState::ParseSampler() {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);

	lua_getfield(m_L, -1, "should_sample");
	luaL_checktype(m_L, -1, LUA_TBOOLEAN);

	if (static_cast<bool>(lua_toboolean(m_L, -1))) {
		lua_pop(m_L, 1);

		lua_getfield(m_L, -1, "samples");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		int num_samples = static_cast<int>(lua_tonumber(m_L, -1));
		lua_pop(m_L, 1);

		lua_getfield(m_L, -1, "sets");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		int num_sets = static_cast<int>(lua_tonumber(m_L, -1));
		lua_pop(m_L, 1);

		lua_getfield(m_L, -1, "sampler");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		int sampler = static_cast<int>(lua_tonumber(m_L, -1));

		if (sampler == 1) {
			std::shared_ptr<Hammersley> newSampler(new Hammersley(num_samples, num_sets));
			worldPtr->m_ViewPlane.SetSampler(newSampler);
	
		} else if (sampler == 2) {
			std::shared_ptr<Jittered> newSampler(new Jittered(num_samples, num_sets));
			worldPtr->m_ViewPlane.SetSampler(newSampler);
	
		} else if (sampler == 3) {
			std::shared_ptr<MultiJittered> newSampler(new MultiJittered(num_samples, num_sets));
			worldPtr->m_ViewPlane.SetSampler(newSampler);
	
		} else if (sampler == 4) {
			std::shared_ptr<NRooks> newSampler(new NRooks(num_samples, num_sets));
			worldPtr->m_ViewPlane.SetSampler(newSampler);
	
		} else if (sampler == 5) {
			std::shared_ptr<PureRandom> newSampler(new PureRandom(num_samples, num_sets));
			worldPtr->m_ViewPlane.SetSampler(newSampler);
	
		} else {
			std::shared_ptr<Regular> newSampler(new Regular(num_samples, num_sets));
			worldPtr->m_ViewPlane.SetSampler(newSampler);
		}

		lua_pop(m_L, 1);
	
	} else {
		lua_pop(m_L, 1);
	
		std::shared_ptr<Regular> newSampler(new Regular(1));
		worldPtr->m_ViewPlane.SetSampler(newSampler);
	}
}

void LuaState::ParseTracer() {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);

	lua_getfield(m_L, -1, "tracer");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	int tracer = static_cast<int>(lua_tonumber(m_L, -1));

	if (tracer == 2) {
		std::shared_ptr<MultipleObjects> newTracer(new MultipleObjects(worldPtr));
		worldPtr->m_TracerPtr = newTracer;
	
	} else {
		std::shared_ptr<RayCast> newTracer(new RayCast(worldPtr));
		worldPtr->m_TracerPtr = newTracer;
	}

	lua_pop(m_L, 1);
}

void LuaState::ParseCamera() {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);

	std::shared_ptr<Pinhole> pinhole_ptr(new Pinhole);

	lua_getfield(m_L, -1, "camera");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	lua_getfield(m_L, -1, "eye");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	pinhole_ptr->SetEye(ParseVector());
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "look_at");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	pinhole_ptr->LookAt(ParseVector());
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "yaw");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	pinhole_ptr->SetYaw(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "pitch");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	pinhole_ptr->SetPitch(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "roll");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	pinhole_ptr->SetRoll(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "exposure_time");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	pinhole_ptr->SetExposureTime(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "vpdistance");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	pinhole_ptr->SetViewPlaneDistance(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "zoom");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	pinhole_ptr->SetZoom(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	worldPtr->SetCamera(pinhole_ptr);
	lua_pop(m_L, 1);
}

void LuaState::ParseLights() {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);

	lua_getfield(m_L, -1, "light_list");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	for (int i = 1;; ++i) {
		lua_rawgeti(m_L, -1, i);

		if (lua_isnil(m_L, -1)) {
			lua_pop(m_L, 1);
			break;
		}

		luaL_checktype(m_L, -1, LUA_TTABLE);

		lua_getfield(m_L, -1, "name");
		luaL_checktype(m_L, -1, LUA_TSTRING);
		std::string name = lua_tostring(m_L, -1);
		lua_pop(m_L, 1);

		std::cout << lua_gettop(m_L) << std::endl;
		if (name == "Point") {
			lua_getfield(m_L, -1, "position");
			luaL_checktype(m_L, -1, LUA_TTABLE);
			glm::vec3 position(ParseVector());
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "color");
			luaL_checktype(m_L, -1, LUA_TTABLE);
			RGBColor color(ParseColor());
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "intensity");
			luaL_checktype(m_L, -1, LUA_TNUMBER);
			float intensity = static_cast<float>(lua_tonumber(m_L, -1));
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "shadows");
			luaL_checktype(m_L, -1, LUA_TBOOLEAN);
			bool shadows = static_cast<bool>(lua_toboolean(m_L, -1));
			lua_pop(m_L, 1);

			std::cout << lua_gettop(m_L) << std::endl;
			std::shared_ptr<PointLight> light_ptr(new PointLight(shadows));
			light_ptr->SetColor(color);
			light_ptr->SetPosition(position);
			light_ptr->SetRadiance(intensity);

			worldPtr->AddLight(light_ptr);

		} else if (name == "Directional") {
			lua_getfield(m_L, -1, "direction");
			luaL_checktype(m_L, -1, LUA_TTABLE);
			glm::vec3 direction(ParseVector());
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "color");
			luaL_checktype(m_L, -1, LUA_TTABLE);
			RGBColor color(ParseColor());
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "intensity");
			luaL_checktype(m_L, -1, LUA_TNUMBER);
			float intensity = static_cast<float>(lua_tonumber(m_L, -1));
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "shadows");
			luaL_checktype(m_L, -1, LUA_TBOOLEAN);
			bool shadows = static_cast<bool>(lua_toboolean(m_L, -1));
			lua_pop(m_L, 1);

			std::shared_ptr<Directional> light_ptr(new Directional(shadows));
			light_ptr->SetColor(color);
			light_ptr->SetDirection(direction);
			light_ptr->SetRadiance(intensity);

			worldPtr->AddLight(light_ptr);
		}

		lua_pop(m_L, 1);
	}

	lua_pop(m_L, 1);
}

void LuaState::ParseObjects() {
	std::shared_ptr<World> worldPtr = m_WorldPtr.lock();
	assert(worldPtr);

	lua_getfield(m_L, -1, "object_list");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	for (int i = 1; ; ++i) {
		lua_rawgeti(m_L, -1, i);

		if (lua_isnil(m_L, -1)) {
			lua_pop(m_L, 1);
			break;
		}

		luaL_checktype(m_L, -1, LUA_TTABLE);

		lua_getfield(m_L, -1, "name");
		luaL_checktype(m_L, -1, LUA_TSTRING);
		std::string name = lua_tostring(m_L, -1);
		lua_pop(m_L, 1);

		if (name == "Plane") {
			lua_getfield(m_L, -1, "point");
			luaL_checktype(m_L, -1, LUA_TTABLE);
			glm::vec3 point(ParseVector());
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "normal");
			luaL_checktype(m_L, -1, LUA_TTABLE);
			glm::vec3 normal(ParseVector());
			lua_pop(m_L, 1);

			std::shared_ptr<Material> material_ptr(ParseMaterial());
			std::shared_ptr<Plane> plane_ptr(new Plane(point, normal));

			plane_ptr->SetMaterial(material_ptr);
			worldPtr->AddObject(plane_ptr);

		} else if (name == "Sphere") {
			lua_getfield(m_L, -1, "center");
			luaL_checktype(m_L, -1, LUA_TTABLE);
			glm::vec3 center(ParseVector());
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "radius");
			luaL_checktype(m_L, -1, LUA_TNUMBER);
			float radius = static_cast<float>(lua_tonumber(m_L, -1));
			lua_pop(m_L, 1);

			std::shared_ptr<Material> material_ptr(ParseMaterial());
			std::shared_ptr<Sphere> sphere_ptr(new Sphere(center, radius));

			sphere_ptr->SetMaterial(material_ptr);
			worldPtr->AddObject(sphere_ptr);
		}

		lua_pop(m_L, 1);
	}

	lua_pop(m_L, 1);
}

glm::vec3 LuaState::ParseVector() {
	glm::vec3 vec;

	lua_getfield(m_L, -1, "x");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	vec.x = static_cast<float>(lua_tonumber(m_L, -1));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "y");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	vec.y = static_cast<float>(lua_tonumber(m_L, -1));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "z");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	vec.z = static_cast<float>(lua_tonumber(m_L, -1));
	lua_pop(m_L, 1);

	return vec;
}

RGBColor LuaState::ParseColor() {
	RGBColor color;

	lua_getfield(m_L, -1, "r");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	color.r = static_cast<float>(lua_tonumber(m_L, -1));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "g");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	color.g = static_cast<float>(lua_tonumber(m_L, -1));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "b");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	color.b = static_cast<float>(lua_tonumber(m_L, -1));
	lua_pop(m_L, 1);

	return color;
}

std::shared_ptr<Material> LuaState::ParseMaterial() {
	lua_getfield(m_L, -1, "material");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	lua_getfield(m_L, -1, "name");
	luaL_checktype(m_L, -1, LUA_TSTRING);
	std::string name = lua_tostring(m_L, -1);
	lua_pop(m_L, 1);

	// TODO: Find a way to better reuse code here.
	if (name == "Matte") {
		std::shared_ptr<Matte> material_ptr(new Matte);

		lua_getfield(m_L, -1, "diffuse_color");
		luaL_checktype(m_L, -1, LUA_TTABLE);
		material_ptr->SetDiffuseColor(ParseColor());
		lua_pop(m_L, 1);

		lua_getfield(m_L, -1, "diffuse_reflection");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		material_ptr->SetDiffuseReflection(static_cast<float>(lua_tonumber(m_L, -1)));
		lua_pop(m_L, 1);

		/* TODO: Implement SetAmbientColor()
		lua_getfield(m_L, -1, "ambient_color");
		luaL_checktype(m_L, -1, LUA_TTABLE);
		material_ptr->SetAmbientColor(ParseColor());
		lua_pop(m_L, 1);
		*/

		lua_getfield(m_L, -1, "ambient_reflection");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		material_ptr->SetAmbientReflection(static_cast<float>(lua_tonumber(m_L, -1)));
		lua_pop(m_L, 1);

		lua_pop(m_L, 1);
		return material_ptr;

	} else {
		std::shared_ptr<Phong> material_ptr(new Phong);

		lua_getfield(m_L, -1, "diffuse_color");
		luaL_checktype(m_L, -1, LUA_TTABLE);
		material_ptr->SetDiffuseColor(ParseColor());
		lua_pop(m_L, 1);

		lua_getfield(m_L, -1, "diffuse_reflection");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		material_ptr->SetDiffuseReflection(static_cast<float>(lua_tonumber(m_L, -1)));
		lua_pop(m_L, 1);

		/* TODO: Implement SetAmbientColor()
		lua_getfield(m_L, -1, "ambient_color");
		luaL_checktype(m_L, -1, LUA_TTABLE);
		material_ptr->SetAmbientColor(ParseColor());
		lua_pop(m_L, 1);
		*/

		lua_getfield(m_L, -1, "ambient_reflection");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		material_ptr->SetAmbientReflection(static_cast<float>(lua_tonumber(m_L, -1)));
		lua_pop(m_L, 1);

		/* TODO: Implement SetSpecularColor()
		lua_getfield(m_L, -1, "specular_color");
		luaL_checktype(m_L, -1, LUA_TTABLE);
		material_ptr->SetSpecularColor(ParseColor());
		lua_pop(m_L, 1);
		*/

		lua_getfield(m_L, -1, "specular_reflection");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		material_ptr->SetSpecularReflection(static_cast<float>(lua_tonumber(m_L, -1)));
		lua_pop(m_L, 1);

		lua_getfield(m_L, -1, "specular_exp");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		material_ptr->SetSpecularExponent(static_cast<float>(lua_tonumber(m_L, -1)));
		lua_pop(m_L, 1);

		lua_pop(m_L, 1);
		return material_ptr;
	}
}