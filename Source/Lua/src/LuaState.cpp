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

#include "Camera.h"
#include "Pinhole.h"

#include "Hammersley.h"
#include "Jittered.h"
#include "MultiJittered.h"
#include "NRooks.h"
#include "PureRandom.h"
#include "Regular.h"

#include "MultipleObjects.h"
#include "RayCast.h"

#include "ViewPlane.h"
#include "World.h"

LuaState::LuaState()
	: m_L(nullptr) {

	m_L = luaL_newstate();  // Creates a new Lua State (may cause memory allocation error).
	luaL_openlibs(m_L);  // Opens all standard Lua libraries into the given LuaState. 
}

LuaState::~LuaState() {
	lua_close(m_L);

	m_L = nullptr;
}

bool LuaState::Start(const std::string &filename) {
	// Loads a file as a Lua chunk.
	if (luaL_loadfile(m_L, filename.c_str()) != LUA_OK) {
		Logger::ErrorLog(lua_tostring(m_L, -1), "LuaState::Load()");
		return false;
	}

	if (lua_pcall(m_L, 0, 0, 0) == LUA_OK)
		return true;

	Logger::ErrorLog(lua_tostring(m_L, -1), "LuaState::Load()");

	return false;
}

void LuaState::LoadScene(World &w) {
	lua_getglobal(m_L, "scene");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	CheckTracer(w);
	LoadImage(w);
	LoadCamera(w);

	lua_pop(m_L, 1);
}

void LuaState::LoadImage(World &w) {
	lua_getfield(m_L, -1, "image");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	lua_getfield(m_L, -1, "width");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	w.m_ViewPlane.SetWidth(static_cast<int>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "height");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	w.m_ViewPlane.SetHeight(static_cast<int>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "pixel_size");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	w.m_ViewPlane.SetPixelSize(static_cast<int>(lua_tonumber(m_L, -1)));
	lua_pop(m_L, 1);

	LoadSampler(w);
	lua_pop(m_L, 1);
}

void LuaState::LoadSampler(World &w) {
	lua_getfield(m_L, -1, "should_sample");
	luaL_checktype(m_L, -1, LUA_TBOOLEAN);

	if (static_cast<bool>(lua_toboolean(m_L, -1))) {
		lua_pop(m_L, 1);
		CheckSampler(w);
	
	} else {
		lua_pop(m_L, 1);
	
		std::shared_ptr<Regular> newSampler(new Regular(1));
		w.m_ViewPlane.SetSampler(newSampler);
	}
}

void LuaState::CheckSampler(World &w) {
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
		w.m_ViewPlane.SetSampler(newSampler);
	
	} else if (sampler == 2) {
		std::shared_ptr<Jittered> newSampler(new Jittered(num_samples, num_sets));
		w.m_ViewPlane.SetSampler(newSampler);
	
	} else if (sampler == 3) {
		std::shared_ptr<MultiJittered> newSampler(new MultiJittered(num_samples, num_sets));
		w.m_ViewPlane.SetSampler(newSampler);
	
	} else if (sampler == 4) {
		std::shared_ptr<NRooks> newSampler(new NRooks(num_samples, num_sets));
		w.m_ViewPlane.SetSampler(newSampler);
	
	} else if (sampler == 5) {
		std::shared_ptr<PureRandom> newSampler(new PureRandom(num_samples, num_sets));
		w.m_ViewPlane.SetSampler(newSampler);
	
	} else {
		std::shared_ptr<Regular> newSampler(new Regular(num_samples, num_sets));
		w.m_ViewPlane.SetSampler(newSampler);
	
	}

	lua_pop(m_L, 1);
}

void LuaState::CheckTracer(World &w) {
	lua_getfield(m_L, -1, "tracer");
	luaL_checktype(m_L, -1, LUA_TNUMBER);
	int tracer = static_cast<int>(lua_tonumber(m_L, -1));

	if (tracer == 2) {
		std::shared_ptr<MultipleObjects> newTracer(new MultipleObjects(std::make_shared<World>(w)));
		w.m_TracerPtr = newTracer;
	
	} else {
		std::shared_ptr<RayCast> newTracer(new RayCast(std::make_shared<World>(w)));
		w.m_TracerPtr = newTracer;
	
	}

	lua_pop(m_L, 1);
}

void LuaState::LoadCamera(World &w) {
	std::shared_ptr<Pinhole> pinhole_ptr(new Pinhole);

	lua_getfield(m_L, -1, "camera");
	luaL_checktype(m_L, -1, LUA_TTABLE);

	lua_getfield(m_L, -1, "eye");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	pinhole_ptr->SetEye(ReadVec());
	lua_pop(m_L, 1);

	lua_getfield(m_L, -1, "look_at");
	luaL_checktype(m_L, -1, LUA_TTABLE);
	pinhole_ptr->LookAt(ReadVec());
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

	w.SetCamera(pinhole_ptr);
	lua_pop(m_L, 1);
}

glm::vec3 LuaState::ReadVec() {
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