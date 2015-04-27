#ifndef QUATERNION_H
#define QUATERNION_H

#include <string.h>
#include <glm/glm.hpp>
#include "Vectors.h"
#include "Matrices.h"

namespace Physics
{
	class Quaternion
	{
	public:
		float w, x, y, z;

		Quaternion()
			: w(0.0f)
			, x(0.0f)
			, y(0.0f)
			, z(0.0f)
		{}

		Quaternion(float value)
			: w(value)
			, x(value)
			, y(value)
			, z(value)
		{}

		Quaternion(float inX, float inY, float inZ, float inW)
			: w(inW)
			, x(inX)
			, y(inY)
			, z(inZ)
		{}

		Quaternion(const Quaternion &rhs)
			: w(rhs.w)
			, x(rhs.x)
			, y(rhs.y)
			, z(rhs.z)
		{}

		Quaternion(Vector3 axis, float angle)
			: w(cos(angle/2))
			, x(axis.x * sin(angle/2))
			, y(axis.y * sin(angle/2))
			, z(axis.z * sin(angle/2))
		{}

		~Quaternion(){}

		Quaternion operator*(Quaternion &rhs);
		void operator*=(const Quaternion &rhs);

		float getMagnitude();

		Quaternion getNormalized();
		Quaternion normalize();

		Quaternion getInverse();
		Quaternion invert();

		Quaternion rotate(Vector3 rotation);
		Quaternion rotate(Quaternion rotation);

		void addScaledVector(const Vector3 &vect, float scale);

		Matrix3 ToMatrix();


	};
}

#endif //QUATERNION_H