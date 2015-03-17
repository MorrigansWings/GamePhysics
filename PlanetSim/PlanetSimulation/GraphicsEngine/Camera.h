#ifndef _CAMERA_H_
#define _CAMERA_H_

#pragma once

#include "../PhysicsEngine/Vectors.h"

class Camera
{
public:
	Camera()
		: position(Vector3(0.0f, 0.0f, 0.0f))
		, rotation(Vector2(-D3DX_PI * 0.5f, 0.0f))
		, radius(10.0f)
		, moveSpeed(1.0f)
		, rotationSpeed(1.0f)
	{}
	Camera(Vector3 pos, Vector2 rot, float rad, float movS, float rotS)
		: position(pos)
		, rotation(rot)
		, radius(rad)
		, moveSpeed(movS)
		, rotationSpeed(rotS)
	{}
	Camera(Camera &cam)
		: position(cam.position)
		, rotation(cam.rotation)
		, radius(cam.radius)
		, moveSpeed(cam.moveSpeed)
		, rotationSpeed(cam.rotationSpeed)
	{}
		
	~Camera(){};

	inline void setRotateX(float rot)
	{
		rotation.x += rot;
		//		if (fabsf(rotation.x) >= 2.0f * D3DX_PI)
		//			rotation.x = 0.0f;
	}
	inline void setRotateY(float rot)
	{
		rotation.y += rot;
//		if (fabsf(rotation.y) >= 2.0f * D3DX_PI)
//			rotation.y = 0.0f;
	}
	inline void setRotate(Vector2 newRot){ rotation = newRot; }
	inline void setPosX(float newVal){ position.x = newVal; }
	inline void setPosY(float newVal){ position.y = newVal; }
	inline void setPosZ(float newVal){ position.z = newVal; }
	inline void setPos(Vector3 newPos){ position = newPos; }
	inline void setRadius(float newVal){ radius = newVal; }

	inline Vector3 getPosition(){ return position; }
	inline Vector2 getRotation(){ return rotation; }
	inline float getRadius() { return radius; }
	inline float getMoveSpeed() { return moveSpeed; }
	inline float getRotationSpeed() { return rotationSpeed; }


private:
	Vector3 position;
	Vector2	rotation;
	float	radius,
			moveSpeed,
			rotationSpeed;
};

#endif //_CAMERA_H_