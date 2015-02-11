#define _USE_MATH_DEFINES

#include "Camera.h"
#include <GLFW/glfw3.h>

const double Camera::TO_RADIANS = M_PI / 180.0;

Camera::Camera(float wWidth, float wHeight, GLFWwindow * wind)
{
	windowLink = wind;
	initCamera();
	windowWidth = (int)wWidth;
	windowHeight = (int)wHeight;

	windowMidX = windowWidth / 2;
	windowMidY = windowHeight / 2;
	
	glfwSetCursorPos(windowLink, (double)windowMidX, (double)windowMidY);
}

Camera::~Camera()
{}

void Camera::initCamera()
{
	position = Vector3::ZERO;
	rotation = Vector3::ZERO;
	speed = Vector3::ZERO;

	movementSpeed = 100.0f;

	pitchSensitivity = 0.2f;
	yawSensitivity = 0.2f;

	holdingForward = false;
	holdingBackward = false;
	holdingLeftStrafe = false;
	holdingRightStrafe = false;
}

const float Camera::toRadians(const float &angleDegrees) const
{
	return angleDegrees * (float)TO_RADIANS;
}

void Camera::handleMouseMove(int mouseX, int mouseY)
{
	float horizMovement = (mouseX - windowMidX + 1) * yawSensitivity;
	float vertMovement = (mouseY - windowMidY) * pitchSensitivity;

	rotation.x += vertMovement;
	rotation.y += horizMovement;

	// Limit looking to vertically up or down
	if (rotation.x < -90)
		rotation.x = -90;
	if (rotation.x > 90)
		rotation.x = 90;

	if (rotation.y < 0)
		rotation.y += 360;
	if (rotation.y > 360)
		rotation.y -= 360;

	glfwSetCursorPos(windowLink, (double)windowMidX, (double)windowMidY);
}

void Camera::move(float deltaTime)
{
	Vector3 movement = Vector3::ZERO;

	double sinXRot = sin(toRadians(rotation.x));
	double cosXRot = cos(toRadians(rotation.x));

	double sinYRot = sin(toRadians(rotation.y));
	double cosYRot = sin(toRadians(rotation.y));

	double pitchLimit = cosXRot;

	if (holdingForward)
	{
		movement.x += -sinYRot * pitchLimit;
		movement.y += -sinXRot;
		movement.z += -cosYRot * pitchLimit;
	}
	if (holdingBackward)
	{
		movement.x += -sinYRot * pitchLimit;
		movement.y += sinXRot;
		movement.z += cosYRot * pitchLimit;
	}
	if (holdingLeftStrafe)
	{
		movement.x += -cosYRot;
		movement.z += -sinYRot;
	}
	if (holdingRightStrafe)
	{
		movement.x += cosYRot;
		movement.z += sinYRot;
	}

	movement.normalize();

	float framerateIndependentFactor = movementSpeed * deltaTime;

	movement *= framerateIndependentFactor;

	position += movement;

}