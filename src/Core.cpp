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
#include "Core.h"

#include "Camera.h"
#include "LuaState.h"
#include "Scene.h"

Core::Core(std::string scene_path) :
	m_ScenePtr(new Scene()),
	m_ScenePath(scene_path) {

}

void Core::Run() {
	std::shared_ptr<LuaState> lua_state(new LuaState(shared_from_this()));
	
	lua_state->Start(m_ScenePath);
	lua_state->LoadScene();

	m_ScenePtr->m_CameraPtr->RenderScene(*m_ScenePtr);

	SaveImage();
}

void Core::SaveImage() {
	int width = m_ScenePtr->m_ProjectionPlane.m_Width;
	int height = m_ScenePtr->m_ProjectionPlane.m_Height;

	FreeImage_Initialise();

	FIBITMAP *bitmap = FreeImage_Allocate(width, height, 24);

	if (!bitmap)
		return;

	for (int i = 0; i < width*height; i++) {
		RGBQUAD color;

		color.rgbRed = static_cast<int>(m_ScenePtr->m_Pixels[i].r * 255);
		color.rgbGreen = static_cast<int>(m_ScenePtr->m_Pixels[i].g * 255);
		color.rgbBlue = static_cast<int>(m_ScenePtr->m_Pixels[i].b * 255);

		FreeImage_SetPixelColor(bitmap, i % width, i / height, &color);
	}


	std::stringstream ss;
	ss << m_ScenePath << "/Scene.png";
	std::string result_path = ss.str();

	if (FreeImage_Save(FIF_PNG, bitmap, result_path.c_str(), 0))
		std::cout << "File saved" << std::endl;

	FreeImage_DeInitialise();
}