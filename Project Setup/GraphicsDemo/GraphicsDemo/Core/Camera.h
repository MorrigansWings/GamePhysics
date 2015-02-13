#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <iostream>
#include <math.h>

#include "Vectors.h"
#include "Quat.h"
#include "GLFW/glfw3.h"

class Camera
{
public:
	static const float TO_RADIANS;

	bool holdingForward;
	bool holdingBackward;
	bool holdingLeftStrafe;
	bool holdingRightStrafe;

	Camera(float windowWidth, float windowHeight, GLFWwindow *wind);
	~Camera();

	void handleMouseMove(int mouseX, int mouseY);

	const float toRadians(const float &angleDegrees) const;

	void move(float deltaTime);

	// INLINE GETTERS
	inline float getPitch() { return m_Pitch; }
	inline float getYaw() { return m_Yaw; }
	inline Vector3 getPosition() { return m_Position; }
	inline Vector3 getRotation() { return m_Rotation; }

	// INLINE SETTERS
	inline void setPitch(float inVal){ m_Pitch = inVal; }
	inline void setYaw(float inVal){ m_Yaw = inVal; }
	inline void setPosition(Vector3 newPos){ m_Position = newPos; }
	inline void setRotation(Vector3 newRot){ m_Rotation = newRot; }

private:
	GLFWwindow *windowLink;

	Vector3 m_Position,
			m_Rotation;

	int		m_WindowWidth, 
			m_WindowHeight,
			m_WindowMidX, 
			m_WindowMidY;

	float	m_FOV,
			m_AspectWidth,
			m_AspectHeight,
			m_Near,
			m_Far,
			m_Pitch,
			m_Yaw;

	Matrix4	m_View,
			m_Proj;

	Quat	m_Orient;

	void initCamera();
};


#endif //CAMERA_H