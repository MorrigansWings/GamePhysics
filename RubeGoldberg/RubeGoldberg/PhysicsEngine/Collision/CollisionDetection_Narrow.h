#ifndef COLLISION_DETECTION_NARROW_H
#define COLLISION_DETECTION_NARROW_H

#include "RigidBodyContact.h"
#include "CollisionPrimitive.h"

namespace Physics
{
	class IntersectionTests
	{
	public:
		static bool sphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane);
		static bool sphereAndSphere(const CollisionSphere &first, const CollisionSphere &second);
		// Sphere and Box?
		static bool boxAndBox(const CollisionBox &first, const CollisionBox &second);
		static bool boxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane);
	};

	struct CollisionData
	{
		Contact *contactArray; // points to first element in contacts
		Contact *contacts;

		int contactsLeft;

		unsigned contactCount;

		float friction;
		float restitution;
		float tolerance; // how close an object needs to be to trigger collision

		inline bool hasMoreContacts() { return contactsLeft > 0; }
		inline void reset(unsigned maxContacts)
		{ 
			contactsLeft = maxContacts; 
			contactCount = 0; 
			contacts = contactArray; 
		}
		void addContacts(unsigned count)
		{
			contactsLeft -= count;
			contactCount += count;
			contacts += count;
		}
	};

	class CollisionDetector
	{
	public:
		static unsigned sphereAndHalfSpace(	const CollisionSphere &sphere, 
											const CollisionPlane &plane, 
											CollisionData *data);

		static unsigned sphereAndTruePlane( const CollisionSphere &sphere,
											const CollisionPlane &plane,
											CollisionData *data);

		static unsigned sphereAndSphere(	const CollisionSphere &one,
											const CollisionSphere &two,
											CollisionData *data);
		
		static unsigned boxAndHalfSpace(	const CollisionBox &box,
											const CollisionPlane &plane,
											CollisionData *data);

		static unsigned boxAndBox(	const CollisionBox &one,
									const CollisionBox &two,
									CollisionData *data);

		static unsigned boxAndPoint(	const CollisionBox &box,
										const Vector3 &point,
										CollisionData *data);

		static unsigned boxAndSphere(	const CollisionBox &box,
										const CollisionSphere &sphere,
										CollisionData *data);

	};
}

#endif // COLLISION_DETECTION_NARROW_H