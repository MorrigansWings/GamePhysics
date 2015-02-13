#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <iostream>
#include <math.h>

#include "Vectors.h"
#include "Matrix.h"
#include "Quat.h"
#include "GLFW/glfw3.h"

class Camera
{
public:
	static const float TO_RADIANS;

	Camera(	const float windowWidth, const float windowHeight, 
			const Vector3 position, const Vector3 direction, const Vector3 up,
			const float fov, const float near, const float far)
		: m_AspectWidth(windowWidth)
		, m_AspectHeight(windowHeight)
		, m_Position(position)
		, m_Direction(direction)
		, m_Up(up)
		, m_FOV(fov)
		, m_Near(near)
		, m_Far(far)
		{}

	~Camera();
	
	Matrix4 getViewMatrix();
	Matrix4 getProjectionMatrix();

	const float toRadians(const float &angleDegrees) const;

	// INLINE GETTERS
	inline float getPitch() { return m_Pitch; }
	inline float getYaw() { return m_Yaw; }
	inline Vector3 getPosition() { return m_Position; }
	inline Vector3 getRotation() { return m_Rotation; }
	inline Vector3 getDirection() { return m_Direction; }
	inline Vector3 getUp() { return m_Up; }

	// INLINE SETTERS
	inline void setPitch(float inVal){ m_Pitch = inVal; }
	inline void setYaw(float inVal){ m_Yaw = inVal; }
	inline void setPosition(Vector3 newPos){ m_Position = newPos; }
	inline void setRotation(Vector3 newRot){ m_Rotation = newRot; }

private:
	GLFWwindow *windowLink;

	Vector3 m_Position,
			m_Rotation,
			m_Direction,
			m_Up;

	int		m_WindowWidth,
			m_WindowHeight;

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