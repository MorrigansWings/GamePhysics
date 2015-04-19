#include "Quaternion.h"

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

Quaternion Quaternion::Normalized()
{


}

Matrix3 Quaternion::ToMatrix()
{
	Matrix3 result;
	result.x0 = 1.0f - ((2 * (this->y * this->y)) + (2 * (this->z * this->z)));
	result.y0 = (2.0f * this->x * this->y) + (2.0f * this->z * this->w);
	result.z0 = (2.0f * this->x * this->z) - (2.0f * this->y * this->w);
	result.x1 = (2.0f * this->x * this->y) - (2.0f * this->z * this->w);
	result.y1 = 1 - ((2.0f * (this->x * this->x)) + (2.0f * (this->z * this->z)));
	result.z1 = (2.0f * this->y * this->z) + (2.0f * this->x * this->w);
	result.x2 = (2.0f * this->x * this->z) + (2.0f * this->y * this->w);
	result.y2 = (2.0f * this->y * this->z) - (2.0f * this->x * this->w);
	result.z2 = 1 - ((2.0f * (this->x * this->x)) + (2.0f * (this->y * this->y)));
	return result;
}