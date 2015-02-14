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
		, m_Orient(1, 0, 0, 0)
		{}

	~Camera();
	
	Matrix4 getViewMatrix();
	Matrix4 getProjectionMatrix();
	void setPerspective(const float& fov, const float& width, const float& height, const float& vNear, const float& vFar);
	inline void setAspect(const float& width, const float& height)
	{
		m_AspectWidth = width;
		m_AspectHeight = height;
	}
	inline void lookAt(const Vector3 &center){ m_Direction = center - m_Position; }


	const float toRadians(const float &angleDegrees) const;

	// INLINE GETTERS
	inline Quat getOrientation() { return m_Orient; }
	inline Vector3 getPosition() { return m_Position; }
	inline Vector3 getRotation() { return m_Rotation; }
	inline Vector3 getDirection() { return m_Direction; }
	inline Vector3 getUp() { return m_Up; }
	inline float getFOV() { return m_FOV; }
	inline float getAspectWidth() { return m_AspectWidth; }
	inline float getAspectHeight() { return m_AspectHeight; }
	inline float getNear() { return m_Near; }
	inline float getFar() { return m_Far; }
	inline float getPitch() { return m_Pitch; }
	inline float getYaw() { return m_Yaw; }

	// INLINE SETTERS
	inline void setOrientation(Quat val) { m_Orient = val; }
	inline void setPosition(Vector3 newPos){ m_Position = newPos; }
	inline void setRotation(Vector3 newRot){ m_Rotation = newRot; }
	inline void setDirection(Vector3 val) { m_Direction = val; }
	inline void setUp(Vector3 val) { m_Up = val; }
	inline void setFOV(float val) { m_FOV = val; }
	inline void setAspectWidth(float val) { m_AspectWidth = val; }
	inline void setAspectHeight(float val) { m_AspectHeight = val; }
	inline void setNear(float val) { m_Near = val; }
	inline void setFar(float val) { m_Far = val; }
	inline void setPitch(float inVal){ m_Pitch = inVal; }
	inline void setYaw(float inVal){ m_Yaw = inVal; }

private:
	GLFWwindow *windowLink;

	Matrix4	m_View,
			m_Proj;

	Quat	m_Orient;

	Vector3 m_Position,
			m_Rotation,
			m_Direction,
			m_Up;

	float	m_FOV,
			m_AspectWidth,
			m_AspectHeight,
			m_Near,
			m_Far,
			m_Pitch,
			m_Yaw;

	void initCamera();
};


#endif //CAMERA_H