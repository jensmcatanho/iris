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
#ifndef CAMERA_H
#define CAMERA_H

#include "Prerequisites.h"

class Camera {
	public:
		Camera();
		Camera(glm::vec3, glm::vec3);

		virtual void RenderScene(const World &w) = 0;
		void ComputeUVW();

		inline void SetEye(const glm::vec3 &);
		inline void LookAt(const glm::vec3 &);
		inline void SetUpVector(const glm::vec3 &);
		inline void SetRollAngle(const float);
		inline void SetExposureTime(const float);

	protected:
		glm::vec3 m_Eye;
		glm::vec3 m_LookAt;
		glm::vec3 m_UpVector;
		glm::vec3 m_U, m_V, m_W;
		float m_RollAngle;
		float m_ExposureTime;
};

#endif