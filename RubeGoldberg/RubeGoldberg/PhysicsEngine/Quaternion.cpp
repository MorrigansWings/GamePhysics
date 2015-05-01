#include "Quaternion.h"

#include <sstream>

using namespace Physics;

Quaternion Quaternion::operator*(Quaternion &rhs)
{
	Quaternion result;
	result.w = this->w * rhs.w - this->x * rhs.x - this->y * rhs.y - this->z * rhs.z;
	result.x = this->w * rhs.x + this->x * rhs.w - this->y * rhs.z - this->z * rhs.y;
	result.y = this->w * rhs.y - this->x * rhs.z + this->y * rhs.w - this->z * rhs.x;
	result.z = this->w * rhs.z + this->x * rhs.y - this->y * rhs.x + this->z * rhs.w;
	return result;
}

void Quaternion::operator*=(const Quaternion &rhs)
{
	Quaternion q = *this;
	this->w =	q.w * rhs.w - q.x * rhs.x -
				q.y * rhs.y - q.z * rhs.z;
	this->x =	q.w * rhs.x + q.x * rhs.w +
				q.y * rhs.z - q.z * rhs.y;
	this->y =	q.w * rhs.y + q.y * rhs.w +
				q.z * rhs.x - q.x * rhs.z;
	this->z =	q.w * rhs.z + q.z * rhs.w +
				q.x * rhs.y - q.y * rhs.x;
}

float Quaternion::getMagnitude()
{
	return	sqrt((this->w * this->w) + (this->x * this->x)
			   + (this->y * this->y) + (this->z * this->z));
}

Quaternion Quaternion::getNormalized()
{
	Quaternion result = Quaternion(0.0f);
	float length = this->getMagnitude();
	result.w = this->w / length;
	result.x = this->x / length;
	result.y = this->y / length;
	result.z = this->z / length;

	return result;
}

void Quaternion::normalize()
{
	float length = this->getMagnitude();
	this->w = this->w / length;
	this->x = this->x / length;
	this->y = this->y / length;
	this->z = this->z / length;
}

Quaternion Quaternion::getInverse()
{
	Quaternion result = Quaternion(*this);
	float length = this->getMagnitude();
	result.x = -result.x / (length * length);
	result.y = -result.y / (length * length);
	result.z = -result.z / (length * length);

	return result;
}

void Quaternion::invert()
{
	float length = this->getMagnitude();
	this->x = -this->x / (length * length);
	this->y = -this->y / (length * length);
	this->z = -this->z / (length * length);
}

void Quaternion::rotate(Vector3 rotation)
{
	Quaternion q(0, rotation.x, rotation.y, rotation.z);
	(*this) *= q;
}

void Quaternion::addScaledVector(const Vector3 &vect, float scale)
{
	Quaternion q(0, vect.x * scale, vect.y * scale, vect.z * scale);
	q *= *this;
	this->w += q.w * (0.5f);
	this->x += q.x * (0.5f);
	this->y += q.y * (0.5f);
	this->z += q.z * (0.5f);
}


Matrix3 Quaternion::ToMatrix()
{
	Matrix3 result;
	result.data[0] =  1.0f - ((2 * (this->y * this->y)) + (2 * (this->z * this->z)));
	result.data[3] =		  (2.0f * this->x * this->y) + (2.0f * this->z * this->w);
	result.data[6] =		  (2.0f * this->x * this->z) - (2.0f * this->y * this->w);
	result.data[1] =		  (2.0f * this->x * this->y) - (2.0f * this->z * this->w);
	result.data[4] =  1.0f - ((2.0f * (this->x * this->x)) + (2.0f * (this->z * this->z)));
	result.data[7] =		  (2.0f * this->y * this->z) + (2.0f * this->x * this->w);
	result.data[2] =		  (2.0f * this->x * this->z) + (2.0f * this->y * this->w);
	result.data[5] =		  (2.0f * this->y * this->z) - (2.0f * this->x * this->w);
	result.data[8] =  1.0f - ((2.0f * (this->x * this->x)) + (2.0f * (this->y * this->y)));
	return result;
}

const std::string Quaternion::toString()
{
	std::stringstream output;
	output << "{ " << this->w << ", ";
	output << this->x << ", ";
	output << this->y << ", ";
	output << this->z << "}" << std::endl;
	return output.str();
}