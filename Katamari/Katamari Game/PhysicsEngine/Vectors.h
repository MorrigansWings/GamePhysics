#ifndef _VECTORS_H_
#define _VECTORS_H_

#pragma once
//#include "..\Dependencies\glew\glew.h"
#include <string>

class Vector2;
class Vector3;
class Vector4;

class Vector2
{
public:
	const static Vector2 ZERO;

	float x, y;

	Vector2()
		: x(0.0f)
		, y(0.0f)
	{}

	Vector2(float inX, float inY)
		:x(inX)
		, y(inY)
	{}

	Vector2(int inX, int inY)
		:x((float)inX)
		, y((float)inY)
	{}

	Vector2(float values[2])
		: x(values[0])
		, y(values[1])
	{}

	const Vector2 operator+(const Vector2 &rhs);
	const Vector2 operator+(const int modifier);
	const Vector2 operator+(const float modifier);
	const Vector2 operator=(const Vector2 &rhs);

	const std::string ToString();
};

class Vector3
{
public:
	const static Vector3 ZERO;

	float x, y, z;

	Vector3()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
	{}

	Vector3(int value)
		: x((float)value)
		, y((float)value)
		, z((float)value)
	{}

	Vector3(float value)
		: x(value)
		, y(value)
		, z(value)
	{}

	// Float constructor for Vector3
	Vector3(float inX, float inY, float inZ)
		: x(inX)
		, y(inY)
		, z(inZ)
	{}

	// Int constructor for Vector3
	Vector3(int inX, int inY, int inZ)
		: x((float)inX)
		, y((float)inY)
		, z((float)inZ)
	{}

	Vector3(float values[3])
		: x(values[0])
		, y(values[1])
		, z(values[2])
	{}

	Vector3(const Vector3 &orig)
		: x(orig.x)
		, y(orig.y)
		, z(orig.z)
	{}

	void invert();
	Vector3 getInverted();
	float magnitude();
	float squareMagnitude();
	Vector3 normalize();
	Vector3 getNormalized();
	Vector3 addScaledVector(const Vector3 &velocity, float t);

	float dot(const Vector3 &second);
	Vector3 cross(const Vector3 &second);

	const Vector4 ConvertToHomogeneous();

	const Vector3 operator+(const int modifier);
	const Vector3 operator+(const float modifier);
	const Vector3 operator+(const Vector3 &rhs);

	const Vector3 operator+=(const float modifier);
	const Vector3 operator+=(const Vector3 &rhs);

	Vector3 operator-(const float modifier);
	Vector3 operator-(const Vector3 &rhs);
	Vector3 operator-(const Vector3 &rhs) const;

	Vector3 operator-=(const float modifier);
	Vector3 operator-=(const Vector3 &rhs);

	const Vector3 operator=(const Vector3 &rhs);

	Vector3 operator*(const float rhs);
	Vector3 operator*=(const float rhs);

	Vector3 operator/(const float rhs);
	Vector3 operator/=(const float rhs);

	const std::string ToString();

	static Vector3 cross(const Vector3 &first, const Vector3 &second);
	static float dot(const Vector3 &first, const Vector3 &second);
};

class Vector4
{
public:
	const static Vector4 ZERO;

	float x, y, z, w;

	Vector4()
		: x(0.0f)
		, y(0.0f)
		, z(0.0f)
		, w(0.0f)
	{}

	Vector4(float value)
		: x(value)
		, y(value)
		, z(value)
		, w(value)
	{}

	Vector4(float inR, float inG, float inB, float inA)
		: x(inR)
		, y(inG)
		, z(inB)
		, w(inA)
	{}

	Vector4(int inR, int inG, int inB, int inA)
		: x((float)inR)
		, y((float)inG)
		, z((float)inB)
		, w((float)inA)
	{}

	Vector4(float values[4])
		: x(values[0])
		, y(values[1])
		, z(values[2])
		, w(values[3])
	{}

	const Vector4 operator+(const Vector4 &rhs);
	const Vector4 operator=(const Vector4 &rhs);

};

#endif // _VECTORS_H_