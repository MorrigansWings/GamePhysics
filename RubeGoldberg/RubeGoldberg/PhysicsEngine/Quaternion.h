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
		float x, y, z, w;


		Quaternion()
			: x(0.0f)
			, y(0.0f)
			, w(0.0f)
			, z(0.0f)
		{}

		Quaternion(float value)
			: x(value)
			, y(value)
			, w(value)
			, z(value)
		{}

		Quaternion(float inX, float inY, float inZ, float inW)
			: x(inX)
			, y(inY)
			, w(inW)
			, z(inZ)
		{}

		~Quaternion(){}

		Quaternion operator*(Quaternion &rhs);

		Quaternion Normalized();

		Matrix3 ToMatrix();






	};
}

#endif //QUATERNION_H