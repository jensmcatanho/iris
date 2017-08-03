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
#include "LuaState.h"
#include "Core.h"

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
#include "Plastic.h"

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

// Scene
#include "ProjectionPlane.h"
#include "Scene.h"

LuaState::LuaState(std::shared_ptr<Core> core_ptr) :
	m_L(nullptr),
	m_CorePtr(core_ptr) {

	m_L = luaL_newstate();
	luaL_openlibs(m_L);
}

LuaState::~LuaState() {
	m_L = nullptr;
}

bool LuaState::Start(const std::string &path) {
	if (luaL_loadfile(m_L, "include/raytracer/lua/config.lua") != LUA_OK) {
		Logger::ErrorLog(lua_tostring(m_L, -1), "LuaState::Load()");
		Logger::SaveLog(path);
		return false;
	}

	std::stringstream ss;
	ss << path << "Scene.lua";
	std::string full_path = ss.str();

	if (lua_pcall(m_L, 0, LUA_MULTRET, 0) == LUA_OK) {
		if (luaL_loadfile(m_L, full_path.c_str()) != LUA_OK) {
			Logger::ErrorLog(lua_tostring(m_L, -1), "LuaState::Load()");
			Logger::SaveLog(path);
			return false;
		}

		if (lua_pcall(m_L, 0, LUA_MULTRET, 0) == LUA_OK)
			return true;
	
	}

	Logger::ErrorLog(lua_tostring(m_L, -1), "LuaState::Load()");
	Logger::SaveLog(path);

	return false;
}

void LuaState::LoadScene() {
	std::shared_ptr<Core> corePtr = m_CorePtr.lock();
	assert(corePtr);
	std::shared_ptr<Scene> worldPtr = corePtr->m_WorldPtr;
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
	std::shared_ptr<Core> corePtr = m_CorePtr.lock();
	assert(corePtr);
	std::shared_ptr<Scene> worldPtr = corePtr->m_WorldPtr;
	assert(worldPtr);

	lua_getfield(m_L, -1, "image");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	lua_getfield(m_L, -1, "width");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	worldPtr->m_ProjectionPlane.SetWidth(static_cast<int>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "height");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	worldPtr->m_ProjectionPlane.SetHeight(static_cast<int>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "pixel_size");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	worldPtr->m_ProjectionPlane.SetPixelSize(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "gamma_correction");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	worldPtr->m_ProjectionPlane.SetGammaCorrection(static_cast<float>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "background_color");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	worldPtr->m_BackgroundColor = ParseColor();
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "clamp_out_of_gamut");
	luaL_checktype(m_L, -1, LUA_TBOOLEAN);
	worldPtr->m_ProjectionPlane.SetGamutDisplay(static_cast<bool>(lua_toboolean(m_L, -1) ? true : false));
	lua_pop(m_L, 1);

	if (worldPtr->m_ProjectionPlane.m_ClampOutOfGamut) {
		lua_getfield(m_L, -1, "clamp_color");
		luaL_checktype(m_L, -1, LUA_TTABLE);
		worldPtr->m_ProjectionPlane.m_ClampColor = ParseColor();
		lua_pop(m_L, 1);
	}

	ParseSampler();
	lua_pop(m_L, 1);
}

void LuaState::ParseSampler() {
	std::shared_ptr<Core> corePtr = m_CorePtr.lock();
	assert(corePtr);
	std::shared_ptr<Scene> worldPtr = corePtr->m_WorldPtr;
	assert(worldPtr);

	lua_getfield(m_L, -1, "should_sample");
	luaL_checktype(m_L, -1, LUA_TBOOLEAN);

	if (lua_toboolean(m_L, -1)) {
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
			worldPtr->m_ProjectionPlane.SetSampler(newSampler);
	
		} else if (sampler == 2) {
			std::shared_ptr<Jittered> newSampler(new Jittered(num_samples, num_sets));
			worldPtr->m_ProjectionPlane.SetSampler(newSampler);
	
		} else if (sampler == 3) {
			std::shared_ptr<MultiJittered> newSampler(new MultiJittered(num_samples, num_sets));
			worldPtr->m_ProjectionPlane.SetSampler(newSampler);
	
		} else if (sampler == 4) {
			std::shared_ptr<NRooks> newSampler(new NRooks(num_samples, num_sets));
			worldPtr->m_ProjectionPlane.SetSampler(newSampler);
	
		} else if (sampler == 5) {
			std::shared_ptr<PureRandom> newSampler(new PureRandom(num_samples, num_sets));
			worldPtr->m_ProjectionPlane.SetSampler(newSampler);
	
		} else {
			std::shared_ptr<Regular> newSampler(new Regular(num_samples, num_sets));
			worldPtr->m_ProjectionPlane.SetSampler(newSampler);
		}

		lua_pop(m_L, 1);
	
	} else {
		lua_pop(m_L, 1);
	
		std::shared_ptr<Regular> newSampler(new Regular(1));
		worldPtr->m_ProjectionPlane.SetSampler(newSampler);
	}
}

void LuaState::ParseTracer() {
	std::shared_ptr<Core> corePtr = m_CorePtr.lock();
	assert(corePtr);
	std::shared_ptr<Scene> worldPtr = corePtr->m_WorldPtr;
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
	std::shared_ptr<Core> corePtr = m_CorePtr.lock();
	assert(corePtr);
	std::shared_ptr<Scene> worldPtr = corePtr->m_WorldPtr;
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
	std::shared_ptr<Core> corePtr = m_CorePtr.lock();
	assert(corePtr);
	std::shared_ptr<Scene> worldPtr = corePtr->m_WorldPtr;
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
			bool shadows = static_cast<bool>(lua_toboolean(m_L, -1) ? true : false);
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "attenuate");
			luaL_checktype(m_L, -1, LUA_TBOOLEAN);
			bool attenuate = static_cast<bool>(lua_toboolean(m_L, -1) ? true : false);
			lua_pop(m_L, 1);

			lua_getfield(m_L, -1, "decay");
			luaL_checktype(m_L, -1, LUA_TNUMBER);
			float decay = static_cast<float>(lua_tonumber(m_L, -1));
			lua_pop(m_L, 1);

			std::shared_ptr<PointLight> light_ptr(new PointLight);
			light_ptr->SetColor(color);
			light_ptr->SetPosition(position);
			light_ptr->SetIntensity(intensity);
			light_ptr->SetAttenuation(attenuate);
			light_ptr->SetDecay(decay);
			light_ptr->CastsShadows(shadows);

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
			bool shadows = static_cast<bool>(lua_toboolean(m_L, -1) ? true : false);
			lua_pop(m_L, 1);

			std::shared_ptr<Directional> light_ptr(new Directional);
			light_ptr->SetColor(color);
			light_ptr->SetDirection(direction);
			light_ptr->SetIntensity(intensity);
			light_ptr->CastsShadows(shadows);

			worldPtr->AddLight(light_ptr);
		}

		lua_pop(m_L, 1);
	}

	lua_pop(m_L, 1);
}

void LuaState::ParseObjects() {
	std::shared_ptr<Core> corePtr = m_CorePtr.lock();
	assert(corePtr);
	std::shared_ptr<Scene> worldPtr = corePtr->m_WorldPtr;
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
			std::shared_ptr<Plane> plane_ptr(new Plane);

			plane_ptr->SetPoint(point);
			plane_ptr->SetNormal(glm::normalize(normal));
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
			std::shared_ptr<Sphere> sphere_ptr(new Sphere);

			sphere_ptr->SetCenter(center);
			sphere_ptr->SetRadius(radius);
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

	lua_getfield(m_L, -1, "ambient_color");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	RGBColor ambient_color = ParseColor();
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "ambient_reflection");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	float ambient_reflection = static_cast<float>(lua_tonumber(m_L, -1));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "diffuse_color");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	RGBColor diffuse_color = ParseColor();
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "diffuse_reflection");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	float diffuse_reflection = static_cast<float>(lua_tonumber(m_L, -1));
	lua_pop(m_L, 1);

	if (name == "Matte") {
		std::shared_ptr<Matte> material_ptr(new Matte);

		std::shared_ptr<Lambertian> ambient_ptr(new Lambertian);
		ambient_ptr->SetDiffuseColor(ambient_color);
		ambient_ptr->SetDiffuseReflection(ambient_reflection);
		material_ptr->SetAmbientBRDF(ambient_ptr);

		std::shared_ptr<Lambertian> diffuse_ptr(new Lambertian);
		diffuse_ptr->SetDiffuseColor(diffuse_color);
		diffuse_ptr->SetDiffuseReflection(diffuse_reflection);
		material_ptr->SetDiffuseBRDF(diffuse_ptr);

		lua_pop(m_L, 1);
		return material_ptr;

	} else {
		std::shared_ptr<Plastic> material_ptr(new Plastic);

		lua_getfield(m_L, -1, "specular_color");
		luaL_checktype(m_L, -1, LUA_TTABLE);
		RGBColor specular_color = ParseColor();
		lua_pop(m_L, 1);

		lua_getfield(m_L, -1, "specular_reflection");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		float specular_reflection = static_cast<float>(lua_tonumber(m_L, -1));
		lua_pop(m_L, 1);

		lua_getfield(m_L, -1, "specular_exp");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		float specular_exp = static_cast<float>(lua_tonumber(m_L, -1));
		lua_pop(m_L, 1);

		std::shared_ptr<Lambertian> ambient_ptr(new Lambertian);
		ambient_ptr->SetDiffuseColor(ambient_color);
		ambient_ptr->SetDiffuseReflection(ambient_reflection);
		material_ptr->SetAmbientBRDF(ambient_ptr);

		std::shared_ptr<Lambertian> diffuse_ptr(new Lambertian);
		diffuse_ptr->SetDiffuseColor(diffuse_color);
		diffuse_ptr->SetDiffuseReflection(diffuse_reflection);
		material_ptr->SetDiffuseBRDF(diffuse_ptr);

		lua_getfield(m_L, -1, "specular_brdf");
		luaL_checktype(m_L, -1, LUA_TNUMBER);
		int brdf = static_cast<int>(lua_tonumber(m_L, -1));
		lua_pop(m_L, 1);

		if (brdf == 2) {
			std::shared_ptr<Phong> specular_ptr(new Phong);
			specular_ptr->SetSpecularColor(specular_color);
			specular_ptr->SetSpecularReflection(specular_reflection);
			specular_ptr->SetSpecularExponent(specular_exp);
			material_ptr->SetSpecularBRDF(specular_ptr);
		
		} else if (brdf == 3) {
			std::shared_ptr<BlinnPhong> specular_ptr(new BlinnPhong);
			specular_ptr->SetSpecularColor(specular_color);
			specular_ptr->SetSpecularReflection(specular_reflection);
			specular_ptr->SetSpecularExponent(specular_exp);
			material_ptr->SetSpecularBRDF(specular_ptr);
		}

		lua_pop(m_L, 1);
		return material_ptr;
	}
}

void LuaState::StackDump(std::string component) {
	int top = lua_gettop(m_L);

	Logger::InfoLog("Initializing stack dumping.", component);

	for (int i = 1; i <= top; i++) {
		int t = lua_type(m_L, i);

		switch (t) {
			case LUA_TSTRING:
				Logger::InfoLog(lua_tostring(m_L, i), component);
				break;

			case LUA_TBOOLEAN:
				Logger::InfoLog(lua_toboolean(m_L, i) ? "true" : "false", component);
				break;

			case LUA_TNUMBER:
				Logger::InfoLog(std::to_string(lua_tonumber(m_L, i)), component);
				break;

			default:
				Logger::InfoLog(lua_typename(m_L, t), component);
				break;
		}
	}

	Logger::InfoLog("Finished stack dumping.", component);
}