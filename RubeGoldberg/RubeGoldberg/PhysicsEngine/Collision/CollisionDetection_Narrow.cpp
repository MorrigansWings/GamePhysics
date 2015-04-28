#include "CollisionDetection_Narrow.h"

using namespace Physics;

/**************************** Intersection Tests *************************/
bool IntersectionTests::sphereAndHalfSpace(const CollisionSphere &sphere, const CollisionPlane &plane)
{
	// Find the distance from the origin
	float ballDistance = Vector3::dot(plane.direction, sphere.getAxis(3)) - sphere.radius;

	// Check for the intersection
	return ballDistance <= plane.offset;
}

bool IntersectionTests::sphereAndSphere(const CollisionSphere &one, const CollisionSphere &two)
{
	// Find the vector between the objects
	Vector3 midline = one.getAxis(3) - two.getAxis(3);

	// See if it is large enough.
	return midline.squareMagnitude() < (one.radius + two.radius)*(one.radius + two.radius);
}

static inline float transformToAxis(const CollisionBox &box, const Vector3 &axis)
{
	return
		box.halfSize.x * abs(Vector3::dot(axis, box.getAxis(0))) +
		box.halfSize.y * abs(Vector3::dot(axis, box.getAxis(1))) +
		box.halfSize.z * abs(Vector3::dot(axis, box.getAxis(2)));
}

static inline bool overlapOnAxis(const CollisionBox &one, const CollisionBox &two,
								const Vector3 &axis, const Vector3 &toCentre)
{
	// Project the half-size of one onto axis
	float oneProject = transformToAxis(one, axis);
	float twoProject = transformToAxis(two, axis);

	// Project this onto the axis
	float distance = abs(Vector3::dot(toCentre, axis));

	// Check for overlap
	return (distance < oneProject + twoProject);
}

bool IntersectionTests::boxAndBox(const CollisionBox &one, const CollisionBox &two)
{
	// Find the vector between the two centers
	Vector3 toCenter = two.getAxis(3) - one.getAxis(3);

	return (
		// Check on box one's axes first
		overlapOnAxis(one, two, one.getAxis(0), toCenter) &&
		overlapOnAxis(one, two, one.getAxis(1), toCenter) &&
		overlapOnAxis(one, two, one.getAxis(2), toCenter) &&

		// And on two's
		overlapOnAxis(one, two, two.getAxis(0), toCenter) &&
		overlapOnAxis(one, two, two.getAxis(1), toCenter) &&
		overlapOnAxis(one, two, two.getAxis(2), toCenter) &&

		// Now on the cross products
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(0), two.getAxis(0)), toCenter) &&
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(0), two.getAxis(1)), toCenter) &&
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(0), two.getAxis(2)), toCenter) &&
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(1), two.getAxis(0)), toCenter) &&
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(1), two.getAxis(1)), toCenter) &&
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(1), two.getAxis(2)), toCenter) &&
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(2), two.getAxis(0)), toCenter) &&
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(2), two.getAxis(1)), toCenter) &&
		overlapOnAxis(one, two, Vector3::cross(one.getAxis(2), two.getAxis(2)), toCenter) );
}

bool IntersectionTests::boxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane)
{
	// Work out the projected radius of the box onto the plane direction
	float projectedRadius = transformToAxis(box, plane.direction);

	// Work out how far the box is from the origin
	float boxDistance = Vector3::dot(plane.direction, box.getAxis(3)) - projectedRadius;

	// Check for the intersection
	return boxDistance <= plane.offset;
}

/**************************** Collision Detector *************************/
static inline float penetrationOnAxis(const CollisionBox &one, const CollisionBox &two,
	const Vector3 &axis, const Vector3 &toCenter)
{
	// Project the half-size of one onto axis
	float oneProject = transformToAxis(one, axis);
	float twoProject = transformToAxis(two, axis);

	// Project this onto the axis
	float distance = abs(Vector3::dot(toCenter, axis));

	return oneProject + twoProject - distance;
}

static inline bool tryAxis(	const CollisionBox &one, const CollisionBox &two,
							Vector3 axis, const Vector3& toCentre, unsigned index,
							float &smallestPenetration, unsigned &smallestCase)
{
	// Make sure we have a normalized axis, and don't check almost parallel axes
	if (axis.squareMagnitude() < 0.0001) return true;
	axis.normalize();

	float penetration = penetrationOnAxis(one, two, axis, toCentre);

	if (penetration < 0) return false;
	if (penetration < smallestPenetration) 
	{
		smallestPenetration = penetration;
		smallestCase = index;
	}
	return true;
}

void fillPointFaceBoxBox(const CollisionBox &one, const CollisionBox &two, const Vector3 &toCentre,
						CollisionData *data, unsigned best, float pen)
{
	Contact* contact = data->contacts;

	// Calculate which face is hit on this axis
	Vector3 normal = one.getAxis(best);
	if (Vector3::dot(one.getAxis(best), toCentre) > 0)
		normal = normal * -1.0f;

	// Work out which vertex of box two we're colliding with.
	// Using toCentre doesn't work!
	Vector3 vertex = two.halfSize;
	if (Vector3::dot(two.getAxis(0), normal) < 0) vertex.x = -vertex.x;
	if (Vector3::dot(two.getAxis(1), normal) < 0) vertex.y = -vertex.y;
	if (Vector3::dot(two.getAxis(2), normal) < 0) vertex.z = -vertex.z;

	// Create the contact data
	contact->contactNormal = normal;
	contact->penetration = pen;
	contact->contactPoint = two.getTransform() * vertex;
	contact->setBodyData(one.body, two.body, data->friction, data->restitution);
}

static inline Vector3 contactPoint(	const Vector3 &pOne, const Vector3 &dOne, float oneSize,
									const Vector3 &pTwo, const Vector3 &dTwo, float twoSize,
									bool useOne)
{
	Vector3 toSt, cOne, cTwo;
	float dpStaOne, dpStaTwo, dpOneTwo, smOne, smTwo;
	float denom, mua, mub;

	smOne = dOne.squareMagnitude();
	smTwo = dTwo.squareMagnitude();
	dpOneTwo = Vector3::dot(dTwo, dOne);

	toSt = pOne - pTwo;
	dpStaOne = Vector3::dot(dOne, toSt);
	dpStaTwo = Vector3::dot(dTwo, toSt);

	denom = smOne * smTwo - dpOneTwo * dpOneTwo;

	// Zero denominator indicates parallel lines
	if (abs(denom) < 0.0001f)
		return useOne ? pOne : pTwo;

	mua = (dpOneTwo * dpStaTwo - smTwo * dpStaOne) / denom;
	mub = (smOne * dpStaTwo - dpOneTwo * dpStaOne) / denom;

	// If either of the edges has the nearest point out
	// of bounds, then the edges aren't crossed, we have
	// an edge-face contact. Our point is on the edge, which
	// we know from the useOne parameter.
	if (mua > oneSize || mua < -oneSize ||
		mub > twoSize || mub < -twoSize)
	{
		return useOne ? pOne : pTwo;
	}
	else
	{
		cOne = pOne + dOne * mua;
		cTwo = pTwo + dTwo * mub;

		return cOne * 0.5 + cTwo * 0.5;
	}
}

unsigned CollisionDetector::sphereAndTruePlane(	const CollisionSphere &sphere,
												const CollisionPlane &plane, 
												CollisionData *data)
{
	// Make sure we have contacts
	if (data->contactsLeft <= 0) return 0;

	// Cache the sphere position
	Vector3 position = sphere.getAxis(3);

	// Find the distance from the plane
	float centreDistance = Vector3::dot(plane.direction, position) - plane.offset;

	// Check if we're within radius
	if (centreDistance * centreDistance > sphere.radius * sphere.radius)
		return 0;

	// Check which side of the plane we're on
	Vector3 normal = plane.direction;
	float penetration = -centreDistance;
	if (centreDistance < 0)
	{
		normal *= -1.0f;
		penetration = -penetration;
	}
	penetration += sphere.radius;

	// Create the contact - it has a normal in the plane direction.
	Contact* contact = data->contacts;
	contact->contactNormal = normal;
	contact->penetration = penetration;
	contact->contactPoint = (position - plane.direction) * centreDistance;
	contact->setBodyData(sphere.body, nullptr, data->friction, data->restitution);

	data->addContacts(1);
	return 1;
}

unsigned CollisionDetector::sphereAndHalfSpace(	const CollisionSphere &sphere,
												const CollisionPlane &plane,
												CollisionData *data)
{
	// Make sure we have contacts
	if (data->contactsLeft <= 0) return 0;

	// Cache the sphere position
	Vector3 position = sphere.getAxis(3);

	// Find the distance from the plane
	float ballDistance = Vector3::dot(plane.direction, position) -
		sphere.radius - plane.offset;

	if (ballDistance >= 0) return 0;

	// Create the contact - it has a normal in the plane direction.
	Contact* contact = data->contacts;
	contact->contactNormal = plane.direction;
	contact->penetration = -ballDistance;
	contact->contactPoint = (position - plane.direction) * (ballDistance + sphere.radius);
	contact->setBodyData(sphere.body, nullptr, data->friction, data->restitution);

	data->addContacts(1);
	return 1;
}

unsigned CollisionDetector::sphereAndSphere(const CollisionSphere &one,
											const CollisionSphere &two,
											CollisionData *data)
{
	// Make sure we have contacts
	if (data->contactsLeft <= 0) return 0;

	// Cache the sphere positions
	Vector3 positionOne = one.getAxis(3);
	Vector3 positionTwo = two.getAxis(3);

	// Find the vector between the objects
	Vector3 midline = positionOne - positionTwo;
	float size = midline.magnitude();

	// See if it is large enough.
	if (size <= 0.0f || size >= one.radius + two.radius)
		return 0;

	// We manually create the normal, because we have the
	// size to hand.
	Vector3 normal = midline * (1.0f / size);

	Contact* contact = data->contacts;
	contact->contactNormal = normal;
	contact->contactPoint = positionOne + midline * 0.5f;
	contact->penetration = (one.radius + two.radius - size);
	contact->setBodyData(one.body, two.body, data->friction, data->restitution);

	data->addContacts(1);
	return 1;
}

unsigned CollisionDetector::boxAndHalfSpace(const CollisionBox &box, const CollisionPlane &plane,
											CollisionData *data)
{
	// Make sure we have contacts
	if (data->contactsLeft <= 0) return 0;

	// Check for intersection
	if (!IntersectionTests::boxAndHalfSpace(box, plane)) return 0;

	// Go through each combination of + and - for each half-size
	static float mults[8][3] = { { 1, 1, 1 }, { -1, 1, 1 }, { 1, -1, 1 }, { -1, -1, 1 },
	{ 1, 1, -1 }, { -1, 1, -1 }, { 1, -1, -1 }, { -1, -1, -1 } };

	Contact* contact = data->contacts;
	unsigned contactsUsed = 0;
	for (unsigned i = 0; i < 8; i++) {

		// Calculate the position of each vertex
		Vector3 vertexPos(mults[i][0], mults[i][1], mults[i][2]);
		vertexPos.setComponentProduct(box.halfSize);
		vertexPos = box.transform.transform(vertexPos);

		// Calculate the distance from the plane
		float vertexDistance = Vector3::dot(vertexPos, plane.direction);

		// Compare this to the plane's distance
		if (vertexDistance <= plane.offset)
		{
			// Create the contact data.
			contact->contactPoint = plane.direction;
			contact->contactPoint *= (vertexDistance - plane.offset);
			contact->contactPoint += vertexPos;
			contact->contactNormal = plane.direction;
			contact->penetration = plane.offset - vertexDistance;

			// Write the appropriate data
			contact->setBodyData(box.body, nullptr, data->friction, data->restitution);

			// Move onto the next contact
			contact++;
			contactsUsed++;
			if (contactsUsed == (unsigned)data->contactsLeft) return contactsUsed;
		}
	}

	data->addContacts(contactsUsed);
	return contactsUsed;
}

unsigned CollisionDetector::boxAndBox(const CollisionBox &one, const CollisionBox &two,
										CollisionData *data)
{
	// Find the vector between the two centers
	Vector3 toCenter = two.getAxis(3) - one.getAxis(3);

	// We start assuming there is no contact
	float pen = FLT_MAX;
	unsigned best = 0xffffff;

	// Now we check each axes, returning if it gives us
	// a separating axis, and keeping track of the axis with
	// the smallest penetration otherwise.
	if(! tryAxis(one, two, one.getAxis(0), toCenter, 0, pen, best)) return 0;
	if(! tryAxis(one, two, one.getAxis(1), toCenter, 1, pen, best)) return 0;
	if(! tryAxis(one, two, one.getAxis(2), toCenter, 2, pen, best)) return 0;

	if(! tryAxis(one, two, two.getAxis(0), toCenter, 3, pen, best)) return 0;
	if(! tryAxis(one, two, two.getAxis(1), toCenter, 4, pen, best)) return 0;
	if(! tryAxis(one, two, two.getAxis(2), toCenter, 5, pen, best)) return 0;

	// Store the best axis-major, in case we run into almost
	// parallel edge collisions later
	unsigned bestSingleAxis = best;

	if(! tryAxis(one, two, Vector3::cross(one.getAxis(0), two.getAxis(0)), toCenter, 6, pen, best)) return 0;
	if(! tryAxis(one, two, Vector3::cross(one.getAxis(0), two.getAxis(1)), toCenter, 7, pen, best)) return 0;
	if(! tryAxis(one, two, Vector3::cross(one.getAxis(0), two.getAxis(2)), toCenter, 8, pen, best)) return 0;
	if(! tryAxis(one, two, Vector3::cross(one.getAxis(1), two.getAxis(0)), toCenter, 9, pen, best)) return 0;
	if(! tryAxis(one, two, Vector3::cross(one.getAxis(1), two.getAxis(1)), toCenter, 10, pen, best)) return 0;
	if(! tryAxis(one, two, Vector3::cross(one.getAxis(1), two.getAxis(2)), toCenter, 11, pen, best)) return 0;
	if(! tryAxis(one, two, Vector3::cross(one.getAxis(2), two.getAxis(0)), toCenter, 12, pen, best)) return 0;
	if(! tryAxis(one, two, Vector3::cross(one.getAxis(2), two.getAxis(1)), toCenter, 13, pen, best)) return 0;
	if(! tryAxis(one, two, Vector3::cross(one.getAxis(2), two.getAxis(2)), toCenter, 14, pen, best)) return 0;

	// Make sure we've got a result.
	if(best == 0xffffff) return 0;

	if (best < 3)
	{
		// We've got a vertex of box two on a face of box one.
		fillPointFaceBoxBox(one, two, toCenter, data, best, pen);
		data->addContacts(1);
		return 1;
	}
	else if (best < 6)
	{
		// We've got a vertex of box one on a face of box two.
		fillPointFaceBoxBox(two, one, toCenter * -1.0f, data, best - 3, pen);
		data->addContacts(1);
		return 1;
	}
	else
	{
		// We've got an edge-edge contact. Find out which axes
		best -= 6;
		unsigned oneAxisIndex = best / 3;
		unsigned twoAxisIndex = best % 3;
		Vector3 oneAxis = one.getAxis(oneAxisIndex);
		Vector3 twoAxis = two.getAxis(twoAxisIndex);
		Vector3 axis = Vector3::cross(oneAxis, twoAxis);
		axis.normalize();

		// The axis should point from box one to box two.
		if (Vector3::dot(axis, toCenter) > 0) axis = axis * -1.0f;

		// Determine which edge has the collision
		Vector3 ptOnOneEdge = one.halfSize;
		Vector3 ptOnTwoEdge = two.halfSize;
		for (unsigned i = 0; i < 3; i++)
		{
			if (i == oneAxisIndex) ptOnOneEdge[i] = 0;
			else if (Vector3::dot(one.getAxis(i), axis) > 0) ptOnOneEdge[i] = -ptOnOneEdge[i];

			if (i == twoAxisIndex) ptOnTwoEdge[i] = 0;
			else if (Vector3::dot(two.getAxis(i), axis) < 0) ptOnTwoEdge[i] = -ptOnTwoEdge[i];
		}

		// Move them into world coordinates 
		ptOnOneEdge = one.transform * ptOnOneEdge;
		ptOnTwoEdge = two.transform * ptOnTwoEdge;

		// So we have a point and a direction for the colliding edges.
		// We need to find out point of closest approach of the two
		// line-segments.
		Vector3 vertex = contactPoint(	ptOnOneEdge, oneAxis, one.halfSize[oneAxisIndex],
										ptOnTwoEdge, twoAxis, two.halfSize[twoAxisIndex],
										bestSingleAxis > 2);

		// We can fill the contact.
		Contact* contact = data->contacts;

		contact->penetration = pen;
		contact->contactNormal = axis;
		contact->contactPoint = vertex;
		contact->setBodyData(one.body, two.body, data->friction, data->restitution);
		data->addContacts(1);
		return 1;
	}
	return 0;
}

unsigned CollisionDetector::boxAndPoint(const CollisionBox &box, const Vector3 &point,
										CollisionData *data)
{
	// Transform the point into box coordinates
	Vector3 relPt = box.transform.transformInverse(point);

	Vector3 normal;

	// Check each axis for the axis with the smallest penetration depth
	float min_depth = box.halfSize.x - abs(relPt.x);
	if (min_depth < 0) return 0;
	normal = box.getAxis(0) * ((relPt.x < 0) ? -1 : 1);

	float depth = box.halfSize.y - abs(relPt.y);
	if (depth < 0) return 0;
	else if (depth < min_depth)
	{
		min_depth = depth;
		normal = box.getAxis(1) * ((relPt.y < 0) ? -1 : 1);
	}

	depth = box.halfSize.z - abs(relPt.z);
	if (depth < 0) return 0;
	else if (depth < min_depth)
	{
		min_depth = depth;
		normal = box.getAxis(2) * ((relPt.z < 0) ? -1 : 1);
	}

	// Compile the contact
	Contact* contact = data->contacts;
	contact->contactNormal = normal;
	contact->contactPoint = point;
	contact->penetration = min_depth;

	contact->setBodyData(box.body, nullptr, data->friction, data->restitution);

	data->addContacts(1);
	return 1;
}

unsigned CollisionDetector::boxAndSphere(const CollisionBox &box, const CollisionSphere &sphere,
										CollisionData *data)
{
	// Transform the center of the sphere into box coordinates
	Vector3 center = sphere.getAxis(3);
	Vector3 relCenter = box.transform.transformInverse(center);

	// Early out check to see if we can exclude the contact
	if (abs(relCenter.x) - sphere.radius > box.halfSize.x ||
		abs(relCenter.y) - sphere.radius > box.halfSize.y ||
		abs(relCenter.z) - sphere.radius > box.halfSize.z)
	{
		return 0;
	}

	Vector3 closestPt(0, 0, 0);
	float dist;

	// Clamp each coordinate to the box.
	dist = relCenter.x;
	if (dist > box.halfSize.x) dist = box.halfSize.x;
	if (dist < -box.halfSize.x) dist = -box.halfSize.x;
	closestPt.x = dist;

	dist = relCenter.y;
	if (dist > box.halfSize.y) dist = box.halfSize.y;
	if (dist < -box.halfSize.y) dist = -box.halfSize.y;
	closestPt.y = dist;

	dist = relCenter.z;
	if (dist > box.halfSize.z) dist = box.halfSize.z;
	if (dist < -box.halfSize.z) dist = -box.halfSize.z;
	closestPt.z = dist;

	// Check we're in contact
	dist = (closestPt - relCenter).squareMagnitude();
	if (dist > sphere.radius * sphere.radius) return 0;

	// Compile the contact
	Vector3 closestPtWorld = box.transform.transform(closestPt);

	Contact* contact = data->contacts;
	contact->contactNormal = (closestPtWorld - center);
	contact->contactNormal.normalize();
	contact->contactPoint = closestPtWorld;
	contact->penetration = sphere.radius - sqrt(dist);
	contact->setBodyData(box.body, sphere.body, data->friction, data->restitution);

	data->addContacts(1);
	return 1;
}
