#ifndef COLLISION_PRIMITIVE_H
#define COLLISION_PRIMITIVE_H

#include "Vectors.h"
#include "Matrices.h"
#include "RigidBody.h"
#include "RigidBodyContact.h"

namespace Physics
{
	class IntersectionTests;
	class CollisionDetector;

	/********************** Collision Geometry ***********************/
	class CollisionPrimitive
	{
	public:
		friend class IntersectionTests;
		friend class CollisionDetector;

		inline void calculateInternals() { transform = body->getTransform() * offset; }
		inline Vector3 getAxis(unsigned index) const { 
			return transform.getColumnVector(index); 
		}
		inline const Matrix4& getTransform() const { return transform; }

		RigidBody *body;
		Matrix4 offset;

	protected:
		Matrix4 transform;
	};

	class CollisionSphere : public CollisionPrimitive
	{
	public:
		float radius;
	};

	class CollisionBox : public CollisionPrimitive
	{
	public:
		Vector3 halfSize;
	};

	class CollisionPlane
	{
	public:
		Vector3 direction;
		float offset;
	};
}

#endif //COLLISION_PRIMITIVE_H