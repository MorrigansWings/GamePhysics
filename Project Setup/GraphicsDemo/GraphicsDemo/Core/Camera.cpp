#define _USE_MATH_DEFINES

#include "Camera.h"
#include <GLFW/glfw3.h>

const float Camera::TO_RADIANS = (float)M_PI / 180.0f;

Camera::~Camera()
{}

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

void Camera::setPerspective(const float& fov, const float& width, const float& height, const float& vNear, const float& vFar)
{
	m_FOV = fov;
	m_AspectWidth = width;
	m_AspectHeight = height;
	m_Near = vNear;
	m_Far = vFar;
}