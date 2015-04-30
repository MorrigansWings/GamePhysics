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

	enum ColliderType
	{
		HALF_SPACE = 0,
		PLANE,
		SPHERE,
		BOX,
		PRIMITIVE
	};

	/********************** Collision Geometry ***********************/
	class CollisionPrimitive
	{
	public:
		friend class IntersectionTests;
		friend class CollisionDetector;

		//CollisionPrimitive()
		//	: type(PRIMITIVE)
		//{}
		CollisionPrimitive(ColliderType t)
			: type(t)
		{}
		~CollisionPrimitive(){};

		inline void calculateInternals() { transform = body->getTransform() * offset; }
		inline Vector3 getAxis(unsigned index) const { 
			return transform.getColumnVector(index); 
		}
		inline const Matrix4& getTransform() const { return transform; }

		inline bool isHalfSpace() { return type == HALF_SPACE; }
		inline bool isPlane() { return type == PLANE; }
		inline bool isSphere() { return type == SPHERE; }
		inline bool isBox() { return type == BOX; }

		RigidBody *body;
		Matrix4 offset;

	protected:
		Matrix4 transform;
		ColliderType type;
	};

	class CollisionSphere : public CollisionPrimitive
	{
	public:
		CollisionSphere()
			: CollisionPrimitive(SPHERE)
		{}
		~CollisionSphere(){}

		float radius;
	};

	class CollisionBox : public CollisionPrimitive
	{
	public:
		CollisionBox()
			: CollisionPrimitive(BOX)
		{}
		~CollisionBox(){}

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