#include "Matrices.h"

using namespace Physics;

Matrix3 Matrix3::operator*(float value)
{
	return Matrix3(	this->x0 * value, this->y0 * value, this->z0 * value,
					this->x1 * value, this->y1 * value, this->z1 * value,
					this->x2 * value, this->y2 * value, this->z2 * value);
}

Vector3 Matrix3::operator*(Vector3 &rhs)
{
	Vector3 result;
	result.x = this->x0 * rhs.x + this->y0 * rhs.y + this->z0 * rhs.z;
	result.y = this->x1 * rhs.x + this->y1 * rhs.y + this->z1 * rhs.z;
	result.z = this->x2 * rhs.x + this->y2 * rhs.y + this->z2 * rhs.z;
	return result;
}

Matrix3 Matrix3::getTranspose()
{
	Matrix3 result;
	result.x0 = this->x0;
	result.x1 = this->y0;
	result.x2 = this->z0;
	result.y0 = this->x1;
	result.y1 = this->y1;
	result.y2 = this->z1;
	result.z0 = this->x2;
	result.z1 = this->y2;
	result.z2 = this->z2;
	return result;
}

float Matrix3::getDeterminant()
{
	return (	(this->x0 * this->y1 * this->z2)
			+	(this->x1 * this->y2 * this->z0)
			+	(this->x2 * this->y0 * this->z1)
			-	(this->x0 * this->y2 * this->z1)
			-	(this->x2 * this->y1 * this->z0)
			-	(this->x1 * this->y0 * this->z2));
}

Matrix3 Matrix3::getInverse()
{
	Matrix3 result;
	result.x0 = y1 * z2 - z1 * y2;
	result.x1 = z1 * x2 - x1 * z2;
	result.x2 = x1 * y2 - y1 * x2;
	result.y0 = z0 * y2 - y0 * z2;
	result.y1 = x0 * z2 - z0 * x2;
	result.y2 = y0 * x2 - x0 * y2;
	result.z0 = y0 * z1 - z0 * y1;
	result.z1 = z0 * x1 - x0 * z1;
	result.z2 = x0 * y1 - y0 * x1;
	return result * getDeterminant();
}
/*****************************************************/
Matrix4 Matrix4::getTranslationWithRotation(Matrix3 &base, Vector3 &trans)
{
	Matrix4 result;
	result.x0 = base.x0;
	result.x1 = base.x1;
	result.x2 = base.x2;
	result.x3 = 0.0f;

	result.y0 = base.y0;
	result.y1 = base.y1;
	result.y2 = base.y2;
	result.y3 = 0.0f;

	result.z0 = base.z0;
	result.z1 = base.z1;
	result.z2 = base.z2;
	result.z3 = 0.0f;

	result.w0 = trans.x;
	result.w1 = trans.y;
	result.w2 = trans.z;
	result.w3 = 1.0f;
	
	return result;
}