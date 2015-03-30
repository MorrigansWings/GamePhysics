#include "Camera.h"

mat4x4 Camera::getViewMatrix( void )
{
	m_Dir = normalize(m_LookAt - m_Pos);

	vec3 pitchAxis = cross(m_Dir, m_Up);

	quat pitchQ = angleAxis(m_Pitch, pitchAxis);
	quat yawQ   = angleAxis(m_Yaw, m_Up);

	quat tmp = normalize(cross(pitchQ, yawQ));

	m_Dir = glm::rotate(tmp, m_Dir);
	m_Pos += m_PosDelta;

	m_LookAt = m_Pos + m_Dir;

	m_View = glm::lookAt(getPos(), m_LookAt, getUp());

	m_Pitch *= 0.5f;
	m_Yaw   *= 0.5f;
	m_PosDelta *= 0.8f;

	return m_View;
}

void Camera::moveForward( const GLfloat& amount )
{
	m_PosDelta += getDir() * amount;
}

void Camera::moveBackward( const GLfloat& amount )
{
	m_PosDelta -= getDir() * amount;
}

void Camera::moveLeft( const GLfloat& amount )
{
	m_PosDelta -= getRight() * amount;
}

void Camera::moveRight( const GLfloat& amount )
{
	m_PosDelta += getRight() * amount;
}

void Camera::setPerspective( const GLfloat& fov, const GLfloat& width, const GLfloat& height, const GLfloat& vNear, const GLfloat& vFar )
{
	m_FOV = fov;
	m_AspectWidth = width;
	m_AspectHeight = height;
	m_Near = vNear;
	m_Far = vFar;
}

void Camera::setDir( const GLfloat& x, const GLfloat& y, const GLfloat& z )
{
	m_Dir.x = x; 
	m_Dir.y = y; 
	m_Dir.z = z;

	m_LookAt = m_Pos + m_Dir;
}

mat4x4 Camera::getProjectionMatrix( void )
{
	if ( ! m_ProjUpdated)
		return m_Proj;

	if (m_AspectWidth <= 0.0f || m_AspectHeight <= 0.0f || m_FOV <= 0.0f)
		return mat4(1.0f);

	m_Proj = glm::perspectiveFov(m_FOV, m_AspectWidth, m_AspectHeight, m_Near, m_Far);

	return m_Proj;
}

void Camera::reset( GLfloat width, GLfloat height )
{
	setPos(m_InitialPos);
	setDir(m_InitialDir);
	setUp(m_InitialUp);

	setPerspective(m_InitialFOV, width, height, m_InitialNear, m_InitialFar);

	m_Pitch = 0.0f;
	m_Yaw = 0.0f;
	m_Speed = m_InitialSpeed;
	m_PosDelta = vec3(0.0f);
}

void Camera::rotate( const GLfloat& amount, const vec3& axis )
{
	//m_Dir = glm::rotate(m_Dir, amount, axis);
	//m_ViewUpdated = true;
}

void Camera::changePitch( const GLfloat& amount )
{
	m_Pitch += amount;

	//Check bounds for the camera pitch
	if (m_Pitch > 360.0f)
		m_Pitch -= 360.0f;
	else if (m_Pitch < -360.0f)
		m_Pitch += 360.0f;
}

void Camera::changeYaw( const GLfloat& amount )
{
	//This controls how the heading is changed if the camera is pointed straight up or down
	//The heading delta direction changes
	if (m_Pitch > radians(90.0f) && m_Pitch < radians(270.0f) || (m_Pitch < radians(-90.0f) && m_Pitch > radians(-270.0f)))
		m_Yaw -= amount;
	else 
		m_Yaw += amount;

	//Check bounds for the camera heading
	if (m_Yaw > 360.0f) 
		m_Yaw -= 360.0f;
	else if (m_Yaw < -360.0f) 
		m_Yaw += 360.0f;
}
