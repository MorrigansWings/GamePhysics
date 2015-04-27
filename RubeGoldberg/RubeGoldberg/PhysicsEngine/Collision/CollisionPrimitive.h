#ifndef COLLISION_PRIMITIVE_H
#define COLLISION_PRIMITIVE_H

#include "Vectors.h"
#include "Matrices.h"
#include "RigidBody.h"

namespace Physics
{
	class IntersectionTests;
	class CollisionDetector;

	class CollisionPrimitive
	{
	public:
		friend class IntersectionTests;
		friend class CollisionDetector;

		RigidBody * body;

		Matrix4 offset;



		void calculateInternals();

		Vector3 getAxis(unsigned index) const
		{
			return transform.getColumnVector(index);
		}

		const Matrix4& getTransform() const
		{
			return transform;
		}


	protected:
		Matrix4 transform;
	};
}


#endif //COLLISION_PRIMITIVE_H