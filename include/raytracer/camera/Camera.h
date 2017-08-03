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
#ifndef CAMERA_H
#define CAMERA_H

#include "Prerequisites.h"

/**
 * @addtogroup Cameras
 * @{
 */

/**
 * A point from which the scene will be rendered.
 * @remarks TODO.
 */

class Camera {
	public:
		/**
		 * Standard constructor.
		 */
		Camera();

		/**
		 * Traces the constructed scene.
		 * @param w Reference to the world.
		 */
		virtual void RenderScene(const Scene &w) = 0;

		/**
		 * Sets the eye location in world coordinates.
		 * @param eye Target eye location.
		 */
		void SetEye(const glm::vec3 &eye);

		/**
		 * Makes the camera look at a given direction.
		 * @param look_at Target look direction.
		 */
		void LookAt(const glm::vec3 &look_at);

		/**
		 * Sets the world up vector.
		 * @param up Target up vector.
		 */
		void SetUpVector(const glm::vec3 &up);

		/**
		 * Sets the yaw angle in radians.
		 * @param yaw Target yaw angle.
		 */
		void SetYaw(const float yaw);

		/**
		 * Sets the pitch angle in radians.
		 * @param pitch Target pitch angle.
		 */
		void SetPitch(const float pitch);

		/**
		 * Sets the roll angle in radians.
		 * @param roll Target roll angle.
		 */
		void SetRoll(const float roll);

		/**
		 * Sets the exposure time.
		 * @param etime Target exposure time.
		 */	
		void SetExposureTime(const float etime);

	protected:
		/**
		 * Computes the orthonormal basis of the camera.
		 */
		void ComputeUVW();
		
		/**
		 * Eye position in world coordinates.
		 */
		glm::vec3 m_Eye;

		/**
		 * Direction the camera is facing.
		 */
		glm::vec3 m_LookAt;

		/**
		 * World's up vector.
		 */
		glm::vec3 m_UpVector;

		/**
		 * X vector of the camera in its coordinate system.
		 */
		glm::vec3 m_U;

		/**
		 * Y vector of the camera in its coordinate system.
		 */
		glm::vec3 m_V;

		/**
		 * Z vector of the camera in its coordinate system.
		 */
		glm::vec3 m_W;

		/**
		 * Yaw angle of the camera.
		 */
		float m_Yaw;

		/**
		 * Pitch angle of the camera.
		 */
		float m_Pitch;

		/**
		 * Roll angle of the camera.
		 */
		float m_Roll;

		/**
		 * Exposure time of the camera.
		 */
		float m_ExposureTime;
};

inline void Camera::SetEye(const glm::vec3 &eye) {
	m_Eye = eye;
}

inline void Camera::LookAt(const glm::vec3 &lookat) {
	m_LookAt = lookat;
}

inline void Camera::SetUpVector(const glm::vec3 &up) {
	m_UpVector = up;
}

inline void Camera::SetYaw(const float yaw) {
	m_Yaw = yaw;
}

inline void Camera::SetPitch(const float pitch) {
	m_Pitch = pitch;
}

inline void Camera::SetRoll(const float roll) {
	m_Roll = roll;
}

inline void Camera::SetExposureTime(const float etime) {
	m_ExposureTime = etime;
}

/**
 * @}
 */

#endif