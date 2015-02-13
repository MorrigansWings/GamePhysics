#include "Vectors.h"
#include <string>
#include <sstream>

/********************** Vector2 ****************************/
const Vector2 Vector2::ZERO = Vector2(0.0f, 0.0f);

const Vector2 Vector2::operator+(const Vector2 &rhs)
{
	Vector2 result = *this;
	result.x += rhs.x;
	result.y += rhs.y;
	return result;
}

const Vector2 Vector2::operator+(const float modifier)
{
	Vector2 result = *this;
	result.x += modifier;
	result.y += modifier;
	return result;
}

const Vector2 Vector2::operator+(const int modifier)
{
	Vector2 result = *this;
	result.x += modifier;
	result.y += modifier;
	return result;
}

const std::string Vector2::ToString()
{
	std::stringstream output;
	output << "{ " << this->x << ", ";
	output << this->y << "}" << std::endl;
	return output.str();
}

const Vector2 Vector2::operator=(const Vector2 &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	return *this;
}

/********************** Vector3 ****************************/
const Vector3 Vector3::ZERO = Vector3(0.0f, 0.0f, 0.0f);

const float Vector3::length()
{
	float squareX = this->x * this->x;
	float squareY = this->y * this->y;
	float squareZ = this->z * this->z;
	return sqrt(squareX + squareY + squareZ);
}

// Normalize this vector3 and return result
const Vector3 Vector3::normalize()
{
	float len = this->length();
	this->x = this->x / len;
	this->y = this->y / len;
	this->z = this->z / len;
	return *this;
}

// Return normalized copy of this vector3
const Vector3 Vector3::getNormalized()
{
	Vector3 result = *this;
	float len = this->length();
	result.x = result.x / len;
	result.y = result.y / len;
	result.z = result.z / len;
	return result;
}

const Vector4 Vector3::ConvertToHomogeneous()
{
	return Vector4(this->x, this->y, this->z, 1.0f);
}


const Vector3 Vector3::operator+(const Vector3 &rhs)
{
	Vector3 result = *this;
	result.x += rhs.x;
	result.y += rhs.y;
	result.z += rhs.z;
	return result;
}

const Vector3 Vector3::operator+(const int modifier)
{
	Vector3 result = *this;
	result.x += modifier;
	result.y += modifier;
	result.z += modifier;
	return result;
}

const Vector3 Vector3::operator+(const float modifier)
{
	Vector3 result = *this;
	result.x += modifier;
	result.y += modifier;
	result.z += modifier;
	return result;
}

const Vector3 Vector3::operator+=(const float modifier)
{
	this->x += modifier;
	this->y += modifier;
	this->z += modifier;
	return *this; 
}

const Vector3 Vector3::operator+=(const Vector3 &rhs)
{
	this->x += rhs.x;
	this->y += rhs.y;
	this->z += rhs.z;
	return *this;
}

Vector3 Vector3::operator-(const float modifier)
{
	this->x -= modifier;
	this->y -= modifier;
	this->z -= modifier;
	return *this;
}

Vector3 Vector3::operator-(const Vector3 &rhs)
{
	this->x -= rhs.x;
	this->y -= rhs.y;
	this->z -= rhs.z;
	return *this;
}

const Vector3 Vector3::operator=(const Vector3 &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	return *this;
}

const Vector3 Vector3::operator*(const float rhs)
{
	Vector3 result = *this; 
	result.x *= rhs;
	result.y *= rhs;
	result.z *= rhs;
	return result;
}

const Vector3 Vector3::operator*=(const float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
	return *this;
}


const std::string Vector3::ToString()
{
	std::stringstream output;
	output << "{ " << this->x << ", ";
	output << this->y << ", ";
	output << this->z << "}" << std::endl;
	return output.str();
}

Vector3 Vector3::cross(const Vector3 &first, const Vector3 &second)
{
	return Vector3(
		first.y * second.z - second.y * first.z,
		first.z * second.x - second.z * first.x,
		first.x * second.y - second.x * first.y);
}

float Vector3::dot(const Vector3 &first, const Vector3 &second)
{
	float result = 0.0f;
	result += first.x * second.x;
	result += first.y * second.y;
	result += first.z * second.z;
	return result;
}

/********************** Vector4 ****************************/

const Vector4 Vector4::ZERO = Vector4(0.0f, 0.0f, 0.0f, 0.0f);

const Vector4 Vector4::operator+(const Vector4 &rhs)
{
	Vector4 result = *this;
	result.x += rhs.x;
	result.y += rhs.y;
	result.z += rhs.z;
	result.w += rhs.w;
	return result;
}

const Vector4 Vector4::operator=(const Vector4 &rhs)
{
	this->x = rhs.x;
	this->y = rhs.y;
	this->z = rhs.z;
	this->w = rhs.w;
	return *this;
}