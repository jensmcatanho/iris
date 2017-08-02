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
#include "Camera.h"

Camera::Camera() :
	m_Eye(glm::vec3(0.0, 0.0, 500.0)),
	m_LookAt(glm::vec3(0.0, 0.0, 0.0)),
	m_UpVector(0.0, 1.0, 0.0),
	m_U(1.0, 0.0, 0.0),
	m_V(0.0, 1.0, 0.0),
	m_W(0.0, 0.0, 1.0),
	m_Yaw(0.0),
	m_Pitch(0.0),
	m_Roll(0.0),
	m_ExposureTime(1.0) {

}

void Camera::ComputeUVW() {
	// Handles singularity of view direction being parallel to the up vector.
	if (m_Eye.x == m_LookAt.x && m_Eye.z == m_LookAt.z && m_Eye.y > m_LookAt.y) {
		// Looking vertically down.
		m_U = glm::vec3(0.0, 0.0, 1.0);
		m_V = glm::vec3(1.0, 0.0, 0.0);
		m_W = glm::vec3(0.0, 1.0, 0.0);
	
	} else if (m_Eye.x == m_LookAt.x && m_Eye.z == m_LookAt.z && m_Eye.y < m_LookAt.y) {
		// Looking vertically up.
		m_U = glm::vec3(1.0, 0.0, 0.0);
		m_V = glm::vec3(0.0, 0.0, 1.0);
		m_W = glm::vec3(0.0, -1.0, 0.0);

	} else {
		// General case.
		m_W = glm::normalize(m_Eye - m_LookAt);
		m_U = glm::normalize(glm::cross(m_UpVector, m_W));
		m_V = glm::cross(m_W, m_U);
	}
}