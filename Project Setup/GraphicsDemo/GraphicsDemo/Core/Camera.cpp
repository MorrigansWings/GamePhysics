#define _USE_MATH_DEFINES

#include "Camera.h"
#include <GLFW/glfw3.h>

const float Camera::TO_RADIANS = (float)M_PI / 180.0f;

Camera::~Camera()
{}

void Camera::initCamera()
{
	m_Position = Vector3::ZERO;
	m_Rotation = Vector3::ZERO;

	m_Pitch = 0.2f;
	m_Yaw = 0.2f;
}

const float Camera::toRadians(const float &angleDegrees) const
{
	return angleDegrees * TO_RADIANS;
}

Matrix4 Camera::getViewMatrix()
{
	m_View = Matrix4::lookAt(getPosition(), getPosition() + getDirection(), getUp());

	return m_View;
}

Matrix4 Camera::getProjectionMatrix()
{
	if (m_AspectWidth <= 0.0f || m_AspectHeight <= 0.0f || m_FOV <= 0.0f)
		return Matrix4(1.0f);

	m_Proj = Matrix4::perspectiveFOV(m_FOV, m_AspectWidth, m_AspectHeight, m_Near, m_Far);

	return m_Proj;
}