#include "Matrices.h"

using namespace Physics;

Matrix3 Matrix3::operator*(float value)
{
	Matrix3 result;
	for (int i = 0; i < 9; ++i)
		result.data[i] *= value;
	return result;
}

Vector3 Matrix3::operator*(const Vector3 &rhs)
{
	return Vector3(	rhs.x * data[0] + rhs.y * data[1] + rhs.z * data[2],
					rhs.x * data[3] + rhs.y * data[4] + rhs.z * data[5],
					rhs.x * data[6] + rhs.y * data[7] + rhs.z * data[8] );
}

void Matrix3::operator*=(const Matrix3 &rhs)
{
	float t1;
	float t2;
	float t3;

	t1 = this->data[0] * rhs.data[0] + this->data[1] * rhs.data[3] + this->data[2] * rhs.data[6];
	t2 = this->data[0] * rhs.data[1] + this->data[1] * rhs.data[4] + this->data[2] * rhs.data[7];
	t3 = this->data[0] * rhs.data[2] + this->data[1] * rhs.data[5] + this->data[2] * rhs.data[8];
	this->data[0] = t1;
	this->data[1] = t2;
	this->data[2] = t3;

	t1 = this->data[3] * rhs.data[0] + this->data[4] * rhs.data[3] + this->data[5] * rhs.data[6];
	t2 = this->data[3] * rhs.data[1] + this->data[4] * rhs.data[4] + this->data[5] * rhs.data[7];
	t3 = this->data[3] * rhs.data[2] + this->data[4] * rhs.data[5] + this->data[5] * rhs.data[8];
	this->data[3] = t1;
	this->data[4] = t2;
	this->data[5] = t3;

	t1 = this->data[6] * rhs.data[0] + this->data[7] * rhs.data[3] + this->data[8] * rhs.data[6];
	t2 = this->data[6] * rhs.data[1] + this->data[7] * rhs.data[4] + this->data[8] * rhs.data[7];
	t3 = this->data[6] * rhs.data[2] + this->data[7] * rhs.data[5] + this->data[8] * rhs.data[8];
	this->data[6] = t1;
	this->data[7] = t2;
	this->data[8] = t3;
}

void Matrix3::operator+=(const Matrix3 &rhs)
{
	this->data[0] += rhs.data[0]; this->data[1] += rhs.data[1]; this->data[2] += rhs.data[2];
	this->data[3] += rhs.data[3]; this->data[4] += rhs.data[4]; this->data[5] += rhs.data[5];
	this->data[6] += rhs.data[6]; this->data[7] += rhs.data[7]; this->data[8] += rhs.data[8];
}

void Matrix3::setSkewSymmetric(const Vector3 vec)
{
	data[0] = data[4] = data[8] = 0;
	data[1] = -vec.z;
	data[2] = vec.y;
	data[3] = vec.z;
	data[5] = -vec.x;
	data[6] = -vec.y;
	data[7] = vec.x;
}

void Matrix3::setComponents(const Vector3 &one, const Vector3 &two, const Vector3 &three)
{
	data[0] = one.x;
	data[1] = two.x;
	data[2] = three.x;
	data[3] = one.y;
	data[4] = two.y;
	data[5] = three.y;
	data[6] = one.z;
	data[7] = two.z;
	data[8] = three.z;
}


void Matrix3::setInertiaTensorCoefficients(float ix, float iy, float iz, float ixy, float ixz, float iyz)
{
	data[0] = ix;
	data[1] = data[3] = -ixy;
	data[2] = data[6] = -ixz;
	data[4] = iy;
	data[5] = data[7] = -iyz;
	data[8] = iz;
}

void Matrix3::setBlockInertiaTensor(const Vector3 &halfSizes, float mass)
{
	Vector3 squares = Vector3::componentProduct(halfSizes, halfSizes);
	
	setInertiaTensorCoefficients(	0.3f*mass*(squares.y + squares.z),
									0.3f*mass*(squares.x + squares.z),
									0.3f*mass*(squares.x + squares.y));
}

Vector3 Matrix3::transformTranspose(Vector3 &vec)
{
	return Vector3(	vec.x * data[0] + vec.y * data[3] + vec.z * data[6],
					vec.x * data[1] + vec.y * data[4] + vec.z * data[7],
					vec.x * data[2] + vec.y * data[5] + vec.z * data[8]);
}

Matrix3 Matrix3::getTranspose()
{
	Matrix3 result;
	result.data[0] = result.data[0];
	result.data[1] = result.data[3];
	result.data[2] = result.data[6];
	result.data[3] = result.data[1];
	result.data[4] = result.data[4];
	result.data[5] = result.data[7];
	result.data[6] = result.data[2];
	result.data[7] = result.data[5];
	result.data[8] = result.data[8];
	return result;
}

float Matrix3::getDeterminant()
{
	float t4 =  data[0] * data[4];
	float t6 =  data[0] * data[5];
	float t8 =  data[1] * data[3];
	float t10 = data[2] * data[3];
	float t12 = data[1] * data[6];
	float t14 = data[2] * data[6];

	return	  t4 * data[8] 
			- t6 * data[7] 
			- t8 * data[8] 
			+ t10 * data[7] 
			+ t12 * data[5] 
			- t14 * data[4];
}

Matrix3 Matrix3::getInverse()
{
	Matrix3 result;
	float det = getDeterminant();
	if (det == 0) return Matrix3();
	
	det = (1.0f) / det;

	result.data[0] =  (data[4] * data[8] - data[5] * data[7]) * det;
	result.data[1] = -(data[1] * data[8] - data[2] * data[7]) * det;
	result.data[2] =  (data[1] * data[5] - data[2] * data[4]) * det;
	result.data[3] = -(data[3] * data[8] - data[5] * data[6]) * det;
	result.data[4] =  (data[0] * data[8] - data[2] * data[6]) * det;
	result.data[5] = -(data[0] * data[5] - data[2] * data[3]) * det;
	result.data[6] =  (data[3] * data[7] - data[4] * data[6]) * det;
	result.data[7] = -(data[0] * data[7] - data[1] * data[6]) * det;
	result.data[8] =  (data[0] * data[4] - data[1] * data[3]) * det;
	return result;
}

void Matrix3::setInverse(const Matrix3 &mat)
{
	float t4 = mat.data[0] * mat.data[4];
	float t6 = mat.data[0] * mat.data[5];
	float t8 = mat.data[1] * mat.data[3];
	float t10 = mat.data[2] * mat.data[3];
	float t12 = mat.data[1] * mat.data[6];
	float t14 = mat.data[2] * mat.data[6];

	// Calculate the determinant
	float t16 = (t4*mat.data[8] - t6*mat.data[7] - t8*mat.data[8] +
		t10*mat.data[7] + t12*mat.data[5] - t14*mat.data[4]);

	// make sure the determinant is non-zero.
	if (t16 == 0.0f) return;
	float t17 = 1.0f / t16;

	data[0] = (mat.data[4] * mat.data[8] - mat.data[5] * mat.data[7])*t17;
	data[1] = -(mat.data[1] * mat.data[8] - mat.data[2] * mat.data[7])*t17;
	data[2] = (mat.data[1] * mat.data[5] - mat.data[2] * mat.data[4])*t17;
	data[3] = -(mat.data[3] * mat.data[8] - mat.data[5] * mat.data[6])*t17;
	data[4] = (mat.data[0] * mat.data[8] - t14)*t17;
	data[5] = -(t6 - t10)*t17;
	data[6] = (mat.data[3] * mat.data[7] - mat.data[4] * mat.data[6])*t17;
	data[7] = -(mat.data[0] * mat.data[7] - t12)*t17;
	data[8] = (t4 - t8)*t17;
}
/*****************************************************/
Vector3 Matrix4::operator*(const Vector3 &rhs) const
{
	return Vector3(
		rhs.x * data[0] + rhs.y * data[1] + rhs.z * data[2] + data[3],
		rhs.x * data[4] + rhs.y * data[5] + rhs.z * data[6] + data[7],
		rhs.x * data[8] + rhs.y * data[9] + rhs.z * data[10] + data[11] );
}

Matrix4 Matrix4::operator*(const Matrix4 &rhs) const
{
	Matrix4 result;
	result.data[0] = (rhs.data[0] * data[0]) + (rhs.data[4] * data[1]) + (rhs.data[8] * data[2]);
	result.data[4] = (rhs.data[0] * data[4]) + (rhs.data[4] * data[5]) + (rhs.data[8] * data[6]);
	result.data[8] = (rhs.data[0] * data[8]) + (rhs.data[4] * data[9]) + (rhs.data[8] * data[10]);

	result.data[1] = (rhs.data[1] * data[0]) + (rhs.data[5] * data[1]) + (rhs.data[9] * data[2]);
	result.data[5] = (rhs.data[1] * data[4]) + (rhs.data[5] * data[5]) + (rhs.data[9] * data[6]);
	result.data[9] = (rhs.data[1] * data[8]) + (rhs.data[5] * data[9]) + (rhs.data[9] * data[10]);

	result.data[2] = (rhs.data[2] * data[0]) + (rhs.data[6] * data[1]) + (rhs.data[10] * data[2]);
	result.data[6] = (rhs.data[2] * data[4]) + (rhs.data[6] * data[5]) + (rhs.data[10] * data[6]);
	result.data[10] = (rhs.data[2] * data[8]) + (rhs.data[6] * data[9]) + (rhs.data[10] * data[10]);

	result.data[3] = (rhs.data[3] * data[0]) + (rhs.data[7] * data[1]) + (rhs.data[11] * data[2]) + data[3];
	result.data[7] = (rhs.data[3] * data[4]) + (rhs.data[7] * data[5]) + (rhs.data[11] * data[6]) + data[7];
	result.data[11] = (rhs.data[3] * data[8]) + (rhs.data[7] * data[9]) + (rhs.data[11] * data[10]) + data[11];

	return result;
}

Vector3 Matrix4::transform(const Vector3 &vector) const
{
	return (*this) * vector;
}

Vector3 Matrix4::transformInverse(const Vector3 &vector) const
{
	Vector3 tmp = vector;
	tmp.x -= data[3];
	tmp.y -= data[7];
	tmp.z -= data[11];
	return Vector3(	tmp.x * data[0] + tmp.y * data[4] + tmp.z * data[8],
					tmp.x * data[1] + tmp.y * data[5] + tmp.z * data[9],
					tmp.x * data[2] + tmp.y * data[6] + tmp.z * data[10] );
}

Vector3 Matrix4::transformDirection(const Vector3 &direction) const
{
	return Vector3(
		direction.x * this->data[0] + direction.y * this->data[1] + direction.z * this->data[2],
		direction.x * this->data[4] + direction.y * this->data[5] + direction.z * this->data[6],
		direction.x * this->data[8] + direction.y * this->data[9] + direction.z * this->data[10]);
}

Vector3 Matrix4::transformInverseDirection(const Vector3 &vector) const
{
	return Vector3(	vector.x * data[0] + vector.y * data[4] + vector.z * data[8],
					vector.x * data[1] + vector.y * data[5] + vector.z * data[9],
					vector.x * data[2] + vector.y * data[6] + vector.z * data[10] );
}

float Matrix4::getDeterminant() const
{
	return -data[8] * data[5] * data[2] +
			data[4] * data[9] * data[2] +
			data[8] * data[1] * data[6] -
			data[0] * data[9] * data[6] -
			data[4] * data[1] * data[10] +
			data[0] * data[5] * data[10];
}

Vector3 Matrix4::getRowVector(int i) const
{
	return Vector3(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]);
}

Vector3 Matrix4::getColumnVector(int i) const
{
	return Vector3(data[i], data[i + 4], data[i + 8]);
}

glm::mat4 Matrix4::GLM()
{
	return glm::mat4(	data[0],	data[1],	data[2],	data[3],
						data[4],	data[5],	data[6],	data[7],
						data[8],	data[9],	data[10],	data[11],
						0.0f,		0.0f,		0.0f,		1.0f );	
}

Matrix4 Matrix4::getRotationMatrix(Matrix3 &base)
{
	return getTranslationWithRotation(base, Vector3(0.0f));
}

Matrix4 Matrix4::getTranslationWithRotation(Matrix3 &base, Vector3 &trans)
{
	Matrix4 result;

	result.data[0] = base.data[0];
	result.data[1] = base.data[1];
	result.data[2] = base.data[2];
	result.data[3] = trans.x;

	result.data[4] = base.data[3];
	result.data[5] = base.data[4];
	result.data[6] = base.data[5];
	result.data[7] = trans.y;

	result.data[8] = base.data[6];
	result.data[9] = base.data[7];
	result.data[10] = base.data[8];
	result.data[11] = trans.z;

	return result;
}