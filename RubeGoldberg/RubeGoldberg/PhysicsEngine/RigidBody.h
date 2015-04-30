#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "Vectors.h"
#include "Matrices.h"
#include "Quaternion.h"

namespace Physics
{
	class RigidBody
	{
	public:
		RigidBody()
			: orientation(Quaternion())
			, inverseInertiaTensor(Matrix3())
			, position(Vector3(0.0f))
			, velocity(Vector3(0.0f))
			, rotation(Vector3(0.0f))
			, angularVelocity(Vector3(0.0f))
			, acceleration(Vector3(0.0f))
			, mass(1.0f)
			, inverseMass((mass > 0) ? (1.0f / mass) : 0.0f) // If mass is 0, set inverse mass to 0
			, linearDamping(0.999f)
			, angularDamping(0.999f)
		{}

		~RigidBody(){};

		void calculateDerivedData();
		void integrate(float duration);
		void clearAccumulators();

		void addVelocity(const Vector3 &deltaVel) { velocity += deltaVel; }
		void addRotation(const Vector3 &deltaRot) { rotation += deltaRot; }
		void addForce(const Vector3 &force) { forceAccum += force; }

		Vector3 convertPointToLocalSpace(const Vector3 &point) const;
		Vector3 convertPointToWorldSpace(const Vector3 &point) const;
		Vector3 convertDirectionToLocalSpace(const Vector3 &direction) const;
		Vector3 convertDirectionToWorldSpace(const Vector3 &direction) const;


		/*  Getters and Setters  */
		Matrix4		getTransform() { return transform; }
		Matrix3		getInertiaTensor() { return inverseInertiaTensor.getInverse(); }
		Matrix3		getInverseInertiaTensor() { return inverseInertiaTensor; }
		Matrix3		getInverseInertiaTensorWorld() { return inverseInertiaTensorWorld; }
		Quaternion	getOrientation() { return orientation; }
		Vector3		getPosition() { return position; }
		Vector3		getVelocity() { return velocity; }
		Vector3		getRotation() { return rotation; }
		Vector3		getAngularVelocity() { return angularVelocity; }
		Vector3		getForceAccumulator() { return forceAccum; }
		Vector3		getTorqueAccumulator() { return torqueAccum; }
		Vector3		getAcceleration() { return acceleration; }
		Vector3		getLastFrameAcceleration() { return lastFrameAcceleration; }
		float		getMass() { return mass; }
		float		getInverseMass() { return inverseMass; }
		float		getLinearDamping() { return linearDamping; }
		float		getAngularDamping() { return angularDamping; }

		inline void setTransform(Matrix4 trans) { transform = trans; }
		inline void setInertiaTensor(Matrix3 &tensor) { inverseInertiaTensor = tensor.getInverse(); }
		inline void setInverseInertiaTensor(Matrix3 itensor){ inverseInertiaTensor = itensor; }
		inline void setInverseInertiaTensorWorld(Matrix3 itensor) { inverseInertiaTensorWorld = itensor; }
		inline void setOrientation(Quaternion orient) { orientation = orient; }
		inline void setPosition(Vector3 pos) { position = pos; }
		inline void setVelocity(Vector3 vel) { velocity = vel; }
		inline void setRotation(Vector3 rot) { rotation = rot; }
		inline void setAngularVelocity(Vector3 angvel) { angularVelocity = angvel; }
		inline void setForceAccumulator(Vector3 acc) { forceAccum = acc; }
		inline void setTorqueAccumulator(Vector3 acc) { torqueAccum = acc; }
		inline void setAcceleration(Vector3 acc) { acceleration = acc; }
		inline void setLastFrameAcceleration(Vector3 acc) { lastFrameAcceleration = acc; }
		inline void setMass(float m) { mass = m; inverseMass = (mass == 0.0f ? 0.0f : 1.0f / mass); }
		inline void setInverseMass(float m) { inverseMass = m; }
		inline void setDamping(float linear, float angular) { linearDamping = linear; angularDamping = angular; }
		inline void setLinearDamping(float linear) { linearDamping = linear; }
		inline void setAngularDamping(float angular) { angularDamping = angular; }

	private:
		Quaternion orientation;

		Matrix3 inverseInertiaTensor;

		Vector3 position,
				velocity,
				rotation,
				angularVelocity;

		float	mass,
				inverseMass,
				linearDamping,
				angularDamping;

		// Derived variables
		Matrix4 transform;

		Matrix3 inverseInertiaTensorWorld; //IIT in world space

		// Force and Torque Accumulators
		Vector3 forceAccum,
				torqueAccum,
				acceleration,
				lastFrameAcceleration;

	};
}

#endif //RIGIDBODY_H