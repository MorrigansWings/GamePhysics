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

		Quaternion(float inW, float inX, float inY, float inZ)
			: w(inW)
			, x(inX)
			, y(inY)
			, z(inZ)
		{}

		~Quaternion(){}

		Quaternion operator*(Quaternion &rhs);

		Quaternion Normalized();

		Matrix3 ToMatrix();






	};
}

#endif //QUATERNION_H