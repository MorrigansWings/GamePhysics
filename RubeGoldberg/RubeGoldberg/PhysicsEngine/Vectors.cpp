#include "Vectors.h"
#include <string>
#include <sstream>

using namespace Physics;

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

void Vector3::clear()
{
	this->x = 0.0f;
	this->y = 0.0f;
	this->z = 0.0f;
}

void Vector3::invert()
{
	this->x = -this->x;
	this->y = -this->y;
	this->z = -this->z;
}

Vector3 Vector3::getInverted()
{
	Vector3 result = Vector3();
	result.x = -this->x;
	result.y = -this->y;
	result.z = -this->z;
	return result;
}

float Vector3::magnitude()
{
	float squareX = this->x * this->x;
	float squareY = this->y * this->y;
	float squareZ = this->z * this->z;
	return sqrt(squareX + squareY + squareZ);
}

float Vector3::squareMagnitude()
{
	float squareX = this->x * this->x;
	float squareY = this->y * this->y;
	float squareZ = this->z * this->z;
	return squareX + squareY + squareZ;
}

// Normalize this vector3 and return result
Vector3 Vector3::normalize()
{
	float len = this->magnitude();
	if (len > 0)
	{
		*this *= 1.0f / len;
	}
//	this->x = this->x / len;
//	this->y = this->y / len;
//	this->z = this->z / len;
	return *this;
}

// Return normalized copy of this vector3
Vector3 Vector3::getNormalized()
{
	Vector3 result = Vector3(*this);
	float len = this->magnitude();
	if (len > 0)
	{
		result *= 1.0f / len;
	}
/*	result.x = result.x / len;
	result.y = result.y / len;
	result.z = result.z / len;*/
	return result;
}

Vector3 Vector3::addScaledVector(const Vector3 &v, float t)
{
	this->x += (v.x * t);
	this->y += (v.y * t);
	this->z += (v.z * t);
	return *this;
}

float Vector3::dot(const Vector3 &second)
{
	float result = 0.0f;
	result += this->x * second.x;
	result += this->y * second.y;
	result += this->z * second.z;
	return result;
}

Vector3 Vector3::cross(const Vector3 &second)
{
	return Vector3(
		this->y * second.z - this->z * second.y,
		this->z * second.x - this->x * second.z,
		this->x * second.y - this->y * second.x);
}

Vector3 Vector3::componentProduct(const Vector3 &second)
{
	return Vector3(this->x * second.x, this->y * second.y, this->z * second.z);
}

const Vector4 Vector3::ConvertToHomogeneous()
{
	return Vector4(this->x, this->y, this->z, 1.0f);
}

const Vector3 Vector3::operator+(const Vector3 &rhs)
{
	Vector3 result = Vector3(*this);
	result.x += rhs.x;
	result.y += rhs.y;
	result.z += rhs.z;
	return result;
}

const Vector3 Vector3::operator+(const int modifier)
{
	Vector3 result = Vector3(*this);
	result.x += modifier;
	result.y += modifier;
	result.z += modifier;
	return result;
}

const Vector3 Vector3::operator+(const float modifier)
{
	Vector3 result = Vector3(*this);
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
	Vector3 result = Vector3(*this);
	result.x -= modifier;
	result.y -= modifier;
	result.z -= modifier;
	return result;
}

Vector3 Vector3::operator-(const Vector3 &rhs)
{
	Vector3 result = Vector3(*this);
	result.x -= rhs.x;
	result.y -= rhs.y;
	result.z -= rhs.z;
	return result;
}

Vector3 Vector3::operator-(const Vector3 &rhs) const
{
	Vector3 result = Vector3(*this);
	result.x -= rhs.x;
	result.y -= rhs.y;
	result.z -= rhs.z;
	return result;
}

Vector3 Vector3::operator-=(const float modifier)
{
	this->x -= modifier;
	this->y -= modifier;
	this->z -= modifier;
	return *this;
}

Vector3 Vector3::operator-=(const Vector3 &rhs)
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

Vector3 Vector3::operator*(const float rhs)
{
	Vector3 result = Vector3(*this);
	result.x *= rhs;
	result.y *= rhs;
	result.z *= rhs;
	return result;
}

Vector3 Vector3::operator*=(const float rhs)
{
	this->x *= rhs;
	this->y *= rhs;
	this->z *= rhs;
	return *this;
}

Vector3 Vector3::operator/(const float rhs)
{
	Vector3 result = Vector3(*this);
	result.x /= rhs;
	result.y /= rhs;
	result.z /= rhs;
	return result;
}

Vector3 Vector3::operator/=(const float rhs)
{
	this->x /= rhs;
	this->y /= rhs;
	this->z /= rhs;
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

Vector3 Vector3::componentProduct(const Vector3 &first, const Vector3 &second)
{
	return Vector3(first.x * second.x, first.y * second.y, first.z * second.z);
}

float Vector3::dot(const Vector3 &first, const Vector3 &second)
{
	float result = 0.0f;
	result += first.x * second.x;
	result += first.y * second.y;
	result += first.z * second.z;
	return result;
}

// Calculate the distance between two vectors
float Vector3::getDistance(const Vector3 &first, const Vector3 &second)
{
	return (second - first).magnitude();
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