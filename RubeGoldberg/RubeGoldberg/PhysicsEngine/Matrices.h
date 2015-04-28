#ifndef MATRICES_H
#define MATRICES_H

#include <string.h>
#include <glm/glm.hpp>
#include "Vectors.h"

namespace Physics
{
	class Matrix3
	{
	public:
		float	data[9];

		Matrix3()
		{
			for (int i = 0; i < 9; ++i)
				data[i] = 0.0f;
		}

		Matrix3(float value)
		{
			for (int i = 0; i < 9; ++i)
				data[i] = value;
		}

		Matrix3(float vals[9])
		{
			for (int i = 0; i < 9; ++i)
				data[i] = vals[i];
		}

		Matrix3(const Vector3 &one, const Vector3 &two, const Vector3 &three)
		{
			setComponents(one, two, three);
		}

		Matrix3(float xzero, float yzero, float zzero, 
				float xone, float yone, float zone,
				float xtwo, float ytwo, float ztwo)
		{
			data[0] = xzero;	data[1] = yzero;	data[2] = zzero;
			data[3] = xone;		data[4] = yone;		data[5] = zone;
			data[6] = xtwo;		data[7] = ytwo;		data[8] = ztwo;
		}

		~Matrix3(){}

		inline glm::mat3 GLM() { return glm::mat3(	data[0],	data[1],	data[2],
													data[3],	data[4],	data[5],
													data[6],	data[7],	data[8] ); }
		Matrix3 operator*(float value);
		Vector3 operator*(const Vector3 &rhs);
		void operator*=(const Matrix3 &rhs);

		void operator+=(const Matrix3 &rhs);

		void setSkewSymmetric(const Vector3 vec);
		void setDiagonals(float a, float b, float c) { setInertiaTensorCoefficients(a, b, c); }
		void setComponents(const Vector3 &one, const Vector3 &two, const Vector3 &three);
		void setInertiaTensorCoefficients(float ix, float iy, float iz, float ixy = 0.0f, float ixz = 0.0f, float iyz = 0.0f);
		void setBlockInertiaTensor(const Vector3 &halfSizes, float mass);

		Vector3 transform(const Vector3 &vec) { return (*this) * vec; }
		Vector3 transformTranspose(Vector3 &vec);

		inline Vector3 getRowVector(int i) { Vector3(data[i * 3], data[i * 3 + 1], data[i * 3 + 2]); }
		inline Vector3 getColumnVector(int i) { return Vector3(data[i], data[i + 3], data[i + 6]); }
		Matrix3 getTranspose();
		float getDeterminant();
		Matrix3 getInverse();

		void setInverse(const Matrix3 &mat);


	};

	class Matrix4
	{
	public:
		float	data[12];

		Matrix4()
		{
			data[1] = data[2] = data[3] = 
			data[4] = data[6] = data[7] =
			data[8] = data[9] = data[11] = 0.0f;
			
			data[0] = data[5] = data[10] = 1.0f;
		}


		inline void setDiagonal(float a, float b, float c)
		{
			data[0] = a;
			data[5] = b;
			data[10] = c;
		}

		Vector3 operator*(const Vector3 &rhs) const;
		Matrix4 operator*(const Matrix4 &rhs) const;

		Vector3 transform(const Vector3 &vector) const;
		Vector3 transformInverse(const Vector3 &vector) const;
		Vector3 transformDirection(const Vector3 &direction) const;
		Vector3 transformInverseDirection(const Vector3 &direction) const;

		float getDeterminant() const;

		Matrix4 getTranslationWithRotation(Matrix3 &base, Vector3 &trans);

		Vector3 getRowVector(int i) const;
		Vector3 getColumnVector(int i) const;

		glm::mat4 GLM();

	};
}



#endif //MATRICES_H