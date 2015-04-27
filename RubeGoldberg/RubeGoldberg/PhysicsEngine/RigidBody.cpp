#include "RigidBody.h"

using namespace Physics;

static inline void transformInertiaTensor(Matrix3 &iitWorld, const Quaternion &q, const Matrix3 &iitBody, const Matrix4 &rotationMatrix)
{
	float t4 =	rotationMatrix.data[0] * iitBody.data[0] +
				rotationMatrix.data[1] * iitBody.data[3] +
				rotationMatrix.data[2] * iitBody.data[6];
	float t9 =	rotationMatrix.data[0] * iitBody.data[1] +
				rotationMatrix.data[1] * iitBody.data[4] +
				rotationMatrix.data[2] * iitBody.data[7];
	float t14 = rotationMatrix.data[0] * iitBody.data[2] +
				rotationMatrix.data[1] * iitBody.data[5] +
				rotationMatrix.data[2] * iitBody.data[8];
	float t28 = rotationMatrix.data[4] * iitBody.data[0] +
				rotationMatrix.data[5] * iitBody.data[3] +
				rotationMatrix.data[6] * iitBody.data[6];
	float t33 = rotationMatrix.data[4] * iitBody.data[1] +
				rotationMatrix.data[5] * iitBody.data[4] +
				rotationMatrix.data[6] * iitBody.data[7];
	float t38 = rotationMatrix.data[4] * iitBody.data[2] +
				rotationMatrix.data[5] * iitBody.data[5] +
				rotationMatrix.data[6] * iitBody.data[8];
	float t52 = rotationMatrix.data[8] * iitBody.data[0] +
				rotationMatrix.data[9] * iitBody.data[3] +
				rotationMatrix.data[10] * iitBody.data[6];
	float t57 = rotationMatrix.data[8] * iitBody.data[1] +
				rotationMatrix.data[9] * iitBody.data[4] +
				rotationMatrix.data[10] * iitBody.data[7];
	float t62 = rotationMatrix.data[8] * iitBody.data[2] +
				rotationMatrix.data[9] * iitBody.data[5] +
				rotationMatrix.data[10] * iitBody.data[8];

	iitWorld.data[0] =	t4*rotationMatrix.data[0] +
						t9*rotationMatrix.data[1] + 
						t14*rotationMatrix.data[2];
	iitWorld.data[1] =	t4*rotationMatrix.data[4] +
						t9*rotationMatrix.data[5] +
						t14*rotationMatrix.data[6];
	iitWorld.data[2] =	t4*rotationMatrix.data[8] +
						t9*rotationMatrix.data[9] +
						t14*rotationMatrix.data[10];
	iitWorld.data[3] =	t28*rotationMatrix.data[0] +
						t33*rotationMatrix.data[1] +
						t38*rotationMatrix.data[2];
	iitWorld.data[4] =	t28*rotationMatrix.data[4] +
						t33*rotationMatrix.data[5] +
						t38*rotationMatrix.data[6];
	iitWorld.data[5] =	t28*rotationMatrix.data[8] +
						t33*rotationMatrix.data[9] +
						t38*rotationMatrix.data[10];
	iitWorld.data[6] =	t52*rotationMatrix.data[0] +
						t57*rotationMatrix.data[1] +
						t62*rotationMatrix.data[2];
	iitWorld.data[7] =	t52*rotationMatrix.data[4] +
						t57*rotationMatrix.data[5] +
						t62*rotationMatrix.data[6];
	iitWorld.data[8] =	t52*rotationMatrix.data[8] +
						t57*rotationMatrix.data[9] +
						t62*rotationMatrix.data[10];
}

static inline void calculateTransformMatrix(Matrix4 &transform, const Vector3 &position, const Quaternion &orientation)
{
	transform.data[0] = 1 - 2 * orientation.y * orientation.y -
							2 * orientation.z * orientation.z;
	transform.data[1] =		2 * orientation.x * orientation.y -
							2 * orientation.w * orientation.z;
	transform.data[2] =		2 * orientation.x * orientation.z +
							2 * orientation.w * orientation.y;
	transform.data[3] =	position.x;

	transform.data[4] =		2 * orientation.x * orientation.y +
							2 * orientation.w * orientation.z;
	transform.data[5] = 1 - 2 * orientation.x * orientation.x -
							2 * orientation.z * orientation.z;
	transform.data[6] =		2 * orientation.y * orientation.z -
							2 * orientation.w * orientation.x;
	transform.data[7] =	position.y;

	transform.data[8] =		2 * orientation.x * orientation.z -
							2 * orientation.w * orientation.y;
	transform.data[9] =		2 * orientation.y * orientation.z +
							2 * orientation.w * orientation.x;
	transform.data[10] = 1 - 2 * orientation.x * orientation.x -
							2 * orientation.y * orientation.y;
	transform.data[11] = position.z;
}

void RigidBody::calculateDerivedData()
{
	calculateTransformMatrix(transform, position, orientation);

	transformInertiaTensor(inverseInertiaTensorWorld, orientation, inverseInertiaTensor, transform);
}

void RigidBody::integrate(float duration)
{
	// Calculate linear acceleration from force
	lastFrameAcceleration = acceleration;
	lastFrameAcceleration.addScaledVector(forceAccum, inverseMass);

	// Calculate angular acceleration from torque
	Vector3 angularAcceleration = inverseInertiaTensorWorld.transform(torqueAccum);

	// Adjust velocities
	velocity.addScaledVector(lastFrameAcceleration, duration);
	rotation.addScaledVector(angularAcceleration, duration);

	// Apply Drag
	velocity *= pow(linearDamping, duration);
	rotation *= pow(angularDamping, duration);

	// Update linear position.
	position.addScaledVector(velocity, duration);

	// Update angular position.
	orientation.addScaledVector(rotation, duration);

	calculateDerivedData();

	// Clear accumulators.
	clearAccumulators();
}

void RigidBody::clearAccumulators()
{
	forceAccum.clear();
	torqueAccum.clear();
}

Vector3 RigidBody::convertPointToLocalSpace(const Vector3 &point) const
{
	return transform.transformInverse(point);
}

Vector3 RigidBody::convertPointToWorldSpace(const Vector3 &point) const
{
	return transform.transform(point);
}

Vector3 RigidBody::convertDirectionToLocalSpace(const Vector3 &direction) const
{
	return transform.transformInverseDirection(direction);
}

Vector3 RigidBody::convertDirectionToWorldSpace(const Vector3 &direction) const
{
	return transform.transformDirection(direction);
}
