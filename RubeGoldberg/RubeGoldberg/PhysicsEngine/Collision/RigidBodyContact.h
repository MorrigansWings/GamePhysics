#ifndef RIGIDBODY_CONTACT_H
#define RIGIDBODY_CONTACT_H

#include "RigidBody.h"
#include "Vectors.h"

namespace Physics
{
	class ContactResolver;

	class Contact
	{
		friend class ContactResolver;
	public:
		RigidBody* body[2];

		Vector3 contactPoint;
		Vector3 contactNormal;

		float penetration;
		float friction; // Lateral friction coefficient
		float restitution; // normal restitution coefficient

		void setBodyData(RigidBody *one, RigidBody *two, float friction, float restitution);

	protected:
		Matrix3 contactToWorld;

		Vector3 contactVelocity;
		Vector3 relativeContactPosition[2];

		float desiredDeltaVelocity;

		void calculateInternals(float duration);
		void swapBodies();
		void calculateDesiredDeltaVelocity(float duration);
		Vector3 calculateLocalVelocity(unsigned bodyIndex, float duration);
		void calculateContactBasis();
		void applyImpulse(const Vector3 &impulse, RigidBody *body, Vector3 *velocityChange, Vector3 *rotationChange);
		void applyVelocityChange(Vector3 velocityChange[2], Vector3 rotationChange[2]);
		void applyPositionChange(Vector3 linearChange[2], Vector3 angularChange[2], float penetration);
		Vector3 calculateFrictionlessImpulse(Matrix3 *inverseInertiaTensor);
		Vector3 calculateFrictionImpulse(Matrix3 *inverseInertiaTensor);
	};

	class ContactResolver
	{
	public:
		ContactResolver(unsigned iterations, float smallestVelocity = 0.01f, float smallestInterpenetration = 0.01f);
		ContactResolver(unsigned velocityIterations, unsigned positionIterations,
						float smallestVelocity = 0.01f, float smallestInterpenetration = 0.01f);
		
		inline bool isValid()
		{
			return	(velocityIterations > 0) && (positionIterations > 0) &&
					(smallestVelocity >= 0.0f) && (smallestInterpenetration >= 0.0f);
		}

		inline void setIterations(unsigned iterations) { velocityIterations = positionIterations = iterations; }
		inline void setIterations(unsigned velIter, unsigned posIter) { velocityIterations = velIter; positionIterations = posIter; }

		inline void setSmallest(float vel, float inter) { smallestVelocity = vel; smallestInterpenetration = inter; }

		void resolveContacts(Contact *contactArray, unsigned numContacts, float duration);

		unsigned velocityIterationsUsed;
		unsigned positionIterationsUsed;

	protected:
		void prepareContacts(Contact *contactArray, unsigned numContacts, float duration);
		void adjustVelocities(Contact *contactArray, unsigned numContacts, float duration);
		void adjustPositions(Contact *contactArray, unsigned numContacts, float duration);

		unsigned velocityIterations;
		unsigned positionIterations;
		float smallestVelocity; // Smallest amount of velocity allowed. smaller = 0
		float smallestInterpenetration; // Smallest amount of interpenetration. smaller = 0;

	private:
		bool validSettings;

	};

	class ContactGenerator
	{
	public:
		virtual unsigned addContact(Contact *contact, unsigned limit) const = 0;
	};
}

#endif //RIGIDBODY_CONTACT_H