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
#ifndef LUASTATE_H
#define LUASTATE_H

#include "Prerequisites.h"

/**
 * @addtogroup Lua
 * @{
 */

/**
 * Lua parser.
 * @remarks TODO.
 */
class LuaState {
	public:
		/**
		 * Constructs a Lua state with a pointer to the world.
		 * @param world_ptr Smart pointer to the world.
		 */
		LuaState(std::shared_ptr<World> world_ptr);

		/**
		 * Standard destructor.
		 */
		~LuaState();

		/**
		 * Initialize the Lua state.
		 * @param  filename Scene file.
		 * @return True, if the state was successfully initialized.
		 */
		bool Start(const std::string &filename);

		/**
		 * Loads the scene from Lua into memory.
		 */
		void LoadScene();

	private:
		/**
		 * Pointer to the Lua state.
		 */
		lua_State *m_L;

		/**
		 * Pointer to the world.
		 */
		std::weak_ptr<World> m_WorldPtr;

		/**
		 * Parses image parameters.
		 */
		void ParseImage();

		/**
		 * Parses sampler parameters.
		 */
		void ParseSampler();

		/**
		 * Parses tracer parameters.
		 */
		void ParseTracer();

		/**
		 * Parses camera parameters.
		 */
		void ParseCamera();

		/**
		 * Parses light paramteres.
		 */
		void ParseLights();

		/**
		 * Parses object parameters.
		 */
		void ParseObjects();

		/**
		 * Parses vectors.
		 * @return 3D vector parsed from Lua.
		 */
		glm::vec3 ParseVector();

		/**
		 * Parses colors.
		 * @return Color parsed from Lua.
		 */
		RGBColor ParseColor();

		/**
		 * Parses materials.
		 * @return Material parsed from Lua.
		 */
		std::shared_ptr<Material> ParseMaterial();

		/**
		* Push into the Logger the contents of the Lua stack.
		*/
		void StackDump(std::string component);
};

/**
 * @}
 */

#endif