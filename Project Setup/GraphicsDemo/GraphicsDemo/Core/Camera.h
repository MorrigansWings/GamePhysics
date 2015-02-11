#ifndef CAMERA_H
#define CAMERA_H

#pragma once

#include <iostream>
#include <math.h>

#include "Vectors.h"
#include "GLFW/glfw3.h"

class Camera
{
protected:
	GLFWwindow *windowLink;

	Vector3 position;
	Vector3 rotation;
	Vector3 speed;

	int windowWidth, windowHeight;
	int windowMidX, windowMidY;

	float movementSpeed;
	float pitchSensitivity;
	float yawSensitivity;

	void initCamera();

public:
	static const double TO_RADIANS;

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
	inline float getPitchSensitivity() { return pitchSensitivity; }
	inline float getYawSensitivity() { return yawSensitivity; }
	inline Vector3 getPosition() { return position; }
	inline Vector3 getRotation() { return rotation; }
	inline Vector3 getSpeed() { return speed; }

	// INLINE SETTERS
	inline void setPitchSensitivity(float inVal){ pitchSensitivity = inVal; }
	inline void setYawSensitivity(float inVal){ yawSensitivity = inVal; }
	inline void setPosition(Vector3 newPos){ position = newPos; }
};


#endif //CAMERA_H