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
#include "State.h"

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

State::State()
	: m_L(nullptr) {

	m_L = luaL_newstate();  // Creates a new Lua state (may cause memory allocation error).
	luaL_openlibs(m_L);  // Opens all standard Lua libraries into the given state. 
}

State::~State() {
	lua_close(m_L);

	m_L = nullptr;
}

bool State::Start(const std::string &filename) {
	// Loads a file as a Lua chunk.
	if (luaL_loadfile(m_L, filename.c_str()) != LUA_OK) {
		Logger::ErrorLog(lua_tostring(m_L, -1), "State::Load()");
		return false;
	}

	if (lua_pcall(m_L, 0, 0, 0) == LUA_OK)
		return true;

	Logger::ErrorLog(lua_tostring(m_L, -1), "State::Load()");

	return false;
}