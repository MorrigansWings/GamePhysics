#include "RigidBodyContact.h"

using namespace Physics;

/**************************** CONTACT *************************/
void Contact::setBodyData(RigidBody *one, RigidBody *two, float friction, float restitution)
{
	this->body[0] = one;
	this->body[1] = two;
	this->friction = friction;
	this->restitution = restitution;
}

void Contact::calculateInternals(float duration)
{
	// swap if first body is null. If still null after, exit
	if (body[0] != nullptr) swapBodies();
	if (body[0] != nullptr) return;

	// generate contact basis
	calculateContactBasis();

	// Store relative positions of the contact to each body
	relativeContactPosition[0] = contactPoint - body[0]->getPosition();
	if (body[1] != nullptr)
		relativeContactPosition[1] = contactPoint - body[1]->getPosition();

	// store relative velocity of the bodies at the contact point.
	contactVelocity = calculateLocalVelocity(0, duration);
	if (body[1]) {
		contactVelocity -= calculateLocalVelocity(1, duration);
	}

	// Calculate the desired change in velocity for resolution
	calculateDesiredDeltaVelocity(duration);
}

void Contact::swapBodies()
{
	contactNormal *= -1.0f;
	RigidBody* temp = body[0];
	body[0] = body[1];
	body[1] = temp;
}

void Contact::calculateDesiredDeltaVelocity(float duration)
{
	const static float velocityLimit = (float)0.25f;

	// Calculate velocity from acceleration
	float velocityFromAcc = 0;

	if (body[0] != nullptr)
		velocityFromAcc += Vector3::dot((body[0]->getLastFrameAcceleration() * duration), contactNormal);

	if (body[1] != nullptr)
		velocityFromAcc -= Vector3::dot((body[1]->getLastFrameAcceleration() * duration), contactNormal);

	// Limit restitution if velocity is low
	float thisRestitution = restitution;
	if (abs(contactVelocity.x) < velocityLimit)
		thisRestitution = (float)0.0f;

	// Combine bounce velocity with removed acceleration velocity
	desiredDeltaVelocity = -contactVelocity.x -
		thisRestitution * (contactVelocity.x - velocityFromAcc);
}

Vector3 Contact::calculateLocalVelocity(unsigned bodyIndex, float duration)
{
	RigidBody *thisBody = body[bodyIndex];

	// Calculate contact point velocity
	Vector3 velocity = Vector3::cross(thisBody->getRotation(), relativeContactPosition[bodyIndex]);
	velocity += thisBody->getVelocity();

	// Convert velocity to local space
	Vector3 contactVelocity = contactToWorld.transformTranspose(velocity);

	Vector3 accVelocity = thisBody->getLastFrameAcceleration() * duration;

	// convert velocity to local space
	accVelocity = contactToWorld.transformTranspose(accVelocity);

	// Ignore contact normal acceleration...? always x?
	accVelocity.x = 0;

	// add velocities!
	contactVelocity += accVelocity;

	return contactVelocity;
}

void Contact::calculateContactBasis()
{
	Vector3 contactTangent[2];

	// If Z axis is closer to X or Y axis
	if (abs(contactNormal.x) > abs(contactNormal.y))
	{
		// scale for normalization
		const float s = 1.0f / sqrt(contactNormal.z * contactNormal.z +
									contactNormal.x * contactNormal.x);

		// new X axis is at right angles to the world Y axis
		contactTangent[0].x = contactNormal.z * s;
		contactTangent[0].y = 0;
		contactTangent[0].z = -contactNormal.x * s;

		// new Y axis is at right angles to the new X and Z axes
		contactTangent[1].x = contactNormal.y * contactTangent[0].x;
		contactTangent[1].y =	contactNormal.z * contactTangent[0].x -
								contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = -contactNormal.y * contactTangent[0].x;
	}
	else
	{
		// scale for normalization
		const float s = 1.0f / sqrt(contactNormal.z * contactNormal.z +
									contactNormal.y * contactNormal.y);

		// new X axis is at right angles to the world X axis
		contactTangent[0].x = 0;
		contactTangent[0].y = -contactNormal.z * s;
		contactTangent[0].z = contactNormal.y * s;

		// new Y axis is at right angles to the new X and Z axes
		contactTangent[1].x =	contactNormal.y * contactTangent[0].z -
								contactNormal.z * contactTangent[0].y;
		contactTangent[1].y = -contactNormal.x * contactTangent[0].z;
		contactTangent[1].z = contactNormal.x * contactTangent[0].y;
	}

	// Make a matrix from the three vectors.
	contactToWorld.setComponents(contactNormal, contactTangent[0], contactTangent[1]);
}

void Contact::applyVelocityChange(Vector3 velocityChange[2], Vector3 rotationChange[2])
{
	// Get inverse mass and inverse inertia tensor in world coordinates.
	Matrix3 inverseInertiaTensor[2];
	inverseInertiaTensor[0] = body[0]->getInverseInertiaTensorWorld();
	if (body[1] != nullptr)
		inverseInertiaTensor[1] = body[1]->getInverseInertiaTensorWorld();

	// We will calculate the impulse for each contact axis
	Vector3 impulseContact;
	if (friction == 0.0f)
		impulseContact = calculateFrictionlessImpulse(inverseInertiaTensor);
	else
		impulseContact = calculateFrictionImpulse(inverseInertiaTensor);

	// Convert impulse to world coordinates
	Vector3 impulse = contactToWorld.transform(impulseContact);

	// Separate linear and angular components
	Vector3 impulsiveTorque = Vector3::cross(relativeContactPosition[0], impulse);
	rotationChange[0] = inverseInertiaTensor[0].transform(impulsiveTorque);
	velocityChange[0].clear();
	velocityChange[0].addScaledVector(impulse, body[0]->getInverseMass());

	// Apply changes
	body[0]->addVelocity(velocityChange[0]);
	body[0]->addRotation(rotationChange[0]);

	if (body[1] != nullptr)
	{
		// Work out body one's linear and angular changes
		Vector3 impulsiveTorque = Vector3::cross(impulse, relativeContactPosition[1]);
		rotationChange[1] = inverseInertiaTensor[1].transform(impulsiveTorque);
		velocityChange[1].clear();
		velocityChange[1].addScaledVector(impulse, -body[1]->getInverseMass());

		// And apply them.
		body[1]->addVelocity(velocityChange[1]);
		body[1]->addRotation(rotationChange[1]);
	}
}

void Contact::applyPositionChange(Vector3 linearChange[2], Vector3 angularChange[2], float penetration)
{
	const float angularLimit = (float)0.2f;
	float angularMove[2];
	float linearMove[2];

	float totalInertia = 0;
	float linearInertia[2];
	float angularInertia[2];

	// Calculate inertia of each object in the direction
	// of the contact normal, due to angular inertia only.
	for (unsigned i = 0; i < 2; i++) if (body[i] != nullptr)
	{
		Matrix3 inverseInertiaTensor = body[i]->getInverseInertiaTensorWorld();

		Vector3 angularInertiaWorld = Vector3::cross(relativeContactPosition[i], contactNormal);
		angularInertiaWorld = inverseInertiaTensor.transform(angularInertiaWorld);
		angularInertiaWorld = Vector3::cross(angularInertiaWorld, relativeContactPosition[i]);
		angularInertia[i] = Vector3::dot(angularInertiaWorld, contactNormal);

		// The linear component is simply the inverse mass
		linearInertia[i] = body[i]->getInverseMass();

		// Keep track of the total inertia from all components
		totalInertia += linearInertia[i] + angularInertia[i];
	}

	// Loop through again calculating and applying the changes
	for (unsigned i = 0; i < 2; i++) if (body[i] != nullptr)
	{
		// The linear and angular movements required are in proportion to
		// the two inverse inertias.
		float sign = (i == 0.0f) ? 1.0f : -1.0f;
		angularMove[i] = sign * penetration * (angularInertia[i] / totalInertia);
		linearMove[i] = sign * penetration * (linearInertia[i] / totalInertia);

		// limit the angular move
		Vector3 projection = relativeContactPosition[i];
		projection.addScaledVector( contactNormal, 
									-relativeContactPosition[i].dot(contactNormal) );

		// Use the small angle approximation for the sine of the angle (i.e.
		// the magnitude would be sine(angularLimit) * projection.magnitude
		// but we approximate sine(angularLimit) to angularLimit).
		float maxMagnitude = angularLimit * projection.magnitude();

		if (angularMove[i] < -maxMagnitude)
		{
			float totalMove = angularMove[i] + linearMove[i];
			angularMove[i] = -maxMagnitude;
			linearMove[i] = totalMove - angularMove[i];
		}
		else if (angularMove[i] > maxMagnitude)
		{
			float totalMove = angularMove[i] + linearMove[i];
			angularMove[i] = maxMagnitude;
			linearMove[i] = totalMove - angularMove[i];
		}

		if (angularMove[i] == 0.0f) // no angular movement = no change
			angularChange[i].clear();
		else
		{
			// Calculate target direction
			Vector3 targetAngularDirection = relativeContactPosition[i].cross(contactNormal);

			Matrix3 inverseInertiaTensor = body[i]->getInverseInertiaTensorWorld();

			// Calculate change needed
			angularChange[i] =	inverseInertiaTensor.transform(targetAngularDirection)
								* (angularMove[i] / angularInertia[i]);
		}

		// Velocity change = along contact normal
		linearChange[i] = contactNormal * linearMove[i];

		// Now we can start to apply the values we've calculated.
		// Apply the linear movement
		Vector3 pos = body[i]->getPosition();
		pos.addScaledVector(contactNormal, linearMove[i]);
		body[i]->setPosition(pos);

		// And the change in orientation
		Quaternion q = body[i]->getOrientation();
		q.addScaledVector(angularChange[i], 1.0f);
		body[i]->setOrientation(q);

		// We need to calculate the derived data for any body that is
		// asleep, so that the changes are reflected in the object's
		// data. Otherwise the resolution will not change the position
		// of the object, and the next collision detection round will
		// have the same penetration.
		if (body[i] != nullptr)
			body[i]->calculateDerivedData();
	}
}

Vector3 Contact::calculateFrictionlessImpulse(Matrix3 *inverseInertiaTensor)
{
	Vector3 impulseContact;

	// Calculate the change in velocity in world space for a 
	// unit impulse towards the contact normal.
	Vector3 deltaVelWorld = Vector3::cross(relativeContactPosition[0], contactNormal);
	deltaVelWorld = inverseInertiaTensor[0].transform(deltaVelWorld);
	deltaVelWorld = Vector3::cross(deltaVelWorld, relativeContactPosition[0]);

	// Calculate change in velocity in contact coordinates
	float deltaVelocity = Vector3::dot(deltaVelWorld, contactNormal);

	// Add the linear component of velocity change
	deltaVelocity += body[0]->getInverseMass();

	// Check if we need to the second body's data
	if (body[1] != nullptr)
	{
		// Go through the same transformation sequence again
		Vector3 deltaVelWorld = Vector3::cross(relativeContactPosition[1], contactNormal);
		deltaVelWorld = inverseInertiaTensor[1].transform(deltaVelWorld);
		deltaVelWorld = Vector3::cross(deltaVelWorld, relativeContactPosition[1]);

		// Add the change in velocity due to rotation
		deltaVelocity += Vector3::dot(deltaVelWorld, contactNormal);

		// Add the change in velocity due to linear motion
		deltaVelocity += body[1]->getInverseMass();
	}

	// Calculate the required size of the impulse
	impulseContact.x = desiredDeltaVelocity / deltaVelocity;
	impulseContact.y = 0;
	impulseContact.z = 0;
	return impulseContact;
}

Vector3 Contact::calculateFrictionImpulse(Matrix3 *inverseInertiaTensor)
{
	Vector3 impulseContact;
	float inverseMass = body[0]->getInverseMass();

	// Calculate matrix to convert between linear and angular quantities.
	Matrix3 impulseToTorque;
	impulseToTorque.setSkewSymmetric(relativeContactPosition[0]);

	// Calculate matrix to convert contact impulse to change in velocity in world coordinates.
	Matrix3 deltaVelWorld = impulseToTorque;
	deltaVelWorld *= inverseInertiaTensor[0];
	deltaVelWorld *= impulseToTorque;
	deltaVelWorld *= -1.0f;

	// Check if we need to add body two's data
	if (body[1] != nullptr)
	{
		// Set the cross product matrix
		impulseToTorque.setSkewSymmetric(relativeContactPosition[1]);

		// Calculate the velocity change matrix
		Matrix3 deltaVelWorld2 = impulseToTorque;
		deltaVelWorld2 *= inverseInertiaTensor[1];
		deltaVelWorld2 *= impulseToTorque;
		deltaVelWorld2 *= -1.0f;

		// Add to the total delta velocity.
		deltaVelWorld += deltaVelWorld2;

		// Add to the inverse mass
		inverseMass += body[1]->getInverseMass();
	}

	// Do a change of basis to convert into contact coordinates.
	Matrix3 deltaVelocity = contactToWorld.getTranspose();
	deltaVelocity *= deltaVelWorld;
	deltaVelocity *= contactToWorld;

	// Add in the linear velocity change
	deltaVelocity.data[0] += inverseMass;
	deltaVelocity.data[4] += inverseMass;
	deltaVelocity.data[8] += inverseMass;

	// Invert to get the impulse needed per unit velocity
	Matrix3 impulseMatrix = deltaVelocity.getInverse();

	// Find the target velocities to kill
	Vector3 velKill(desiredDeltaVelocity,
		-contactVelocity.y,
		-contactVelocity.z);

	// Find the impulse to kill target velocities
	impulseContact = impulseMatrix.transform(velKill);

	// Check for exceeding friction
	float planarImpulse = sqrt( impulseContact.y * impulseContact.y +
								impulseContact.z * impulseContact.z );
	
	if (planarImpulse > impulseContact.x * friction)
	{
		// We need to use dynamic friction
		impulseContact.y /= planarImpulse;
		impulseContact.z /= planarImpulse;

		impulseContact.x =	deltaVelocity.data[0] +
							deltaVelocity.data[1] * friction*impulseContact.y +
							deltaVelocity.data[2] * friction*impulseContact.z;
		impulseContact.x = desiredDeltaVelocity / impulseContact.x;
		impulseContact.y *= friction * impulseContact.x;
		impulseContact.z *= friction * impulseContact.x;
	}
	return impulseContact;
}

/**************************** CONTACT RESOLVER *************************/
ContactResolver::ContactResolver(unsigned iterations, float smallestVelocity, float smallestPosition)
{
	setIterations(iterations, iterations);
	setSmallest(smallestVelocity, smallestPosition);
}

ContactResolver::ContactResolver(unsigned velocityIterations, unsigned positionIterations,
								float smallestVelocity, float smallestPosition)
{
	setIterations(velocityIterations);
	setSmallest(smallestVelocity, smallestPosition);
}

void ContactResolver::resolveContacts(Contact *contacts, unsigned numContacts, float duration)
{
	// Make sure we have something to do.
	if (numContacts == 0) return;
	if (!isValid()) return;

	// Prepare the contacts for processing
	prepareContacts(contacts, numContacts, duration);

	// Resolve the interpenetration problems with the contacts.
	adjustPositions(contacts, numContacts, duration);

	// Resolve the velocity problems with the contacts.
	adjustVelocities(contacts, numContacts, duration);
}

void ContactResolver::prepareContacts(Contact* contacts, unsigned numContacts, float duration)
{
	// Generate contact velocity and axis information.
	Contact* lastContact = contacts + numContacts;
	for (Contact* contact = contacts; contact < lastContact; contact++)
		contact->calculateInternals(duration);
}

void ContactResolver::adjustVelocities(Contact *contacts, unsigned numContacts, float duration)
{
	Vector3 velocityChange[2], rotationChange[2];
	Vector3 deltaVel;

	// iteratively handle impacts in order of severity.
	velocityIterationsUsed = 0;
	while (velocityIterationsUsed < velocityIterations)
	{
		// Find contact with maximum magnitude of probable velocity change.
		float max = smallestVelocity;
		unsigned index = numContacts;
		for (unsigned i = 0; i < numContacts; i++)
		{
			if (contacts[i].desiredDeltaVelocity > max)
			{
				max = contacts[i].desiredDeltaVelocity;
				index = i;
			}
		}
		if (index == numContacts) break;

		// Do the resolution on the contact that came out top.
		contacts[index].applyVelocityChange(velocityChange, rotationChange);

		// With the change in velocity of the two bodies, the update of
		// contact velocities means that some of the relative closing
		// velocities need recomputing.
		for (unsigned i = 0; i < numContacts; i++)
		{
			// Check each body in the contact
			for (unsigned b = 0; b < 2; b++) if (contacts[i].body[b])
			{
				// Check for a match with each body in the newly
				// resolved contact
				for (unsigned d = 0; d < 2; d++)
				{
					if (contacts[i].body[b] == contacts[index].body[d])
					{
						deltaVel = velocityChange[d] +
							rotationChange[d].cross(contacts[i].relativeContactPosition[b]);

						// The sign of the change is negative if we're dealing
						// with the second body in a contact.
						contacts[i].contactVelocity += 
										contacts[i].contactToWorld.transformTranspose(deltaVel)
										* (b ? -1.0f : 1.0f);
						contacts[i].calculateDesiredDeltaVelocity(duration);
					}
				}
			}
		}
		velocityIterationsUsed++;
	}
}

void ContactResolver::adjustPositions(Contact *contacts, unsigned numContacts, float duration)
{
	unsigned i, index;
	Vector3 linearChange[2], angularChange[2];
	float max;
	Vector3 deltaPosition;

	// iteratively resolve interpenetrations in order of severity.
	positionIterationsUsed = 0;
	while (positionIterationsUsed < positionIterations)
	{
		// Find biggest penetration
		max = smallestInterpenetration;
		index = numContacts;
		for (i = 0; i < numContacts; i++)
		{
			if (contacts[i].penetration > max)
			{
				max = contacts[i].penetration;
				index = i;
			}
		}
		if (index == numContacts) break;

		// Resolve the penetration.
		contacts[index].applyPositionChange(linearChange, angularChange, max);

		// Again this action may have changed the penetration of other
		// bodies, so we update contacts.
		for (i = 0; i < numContacts; i++)
		{
			// Check each body in the contact
			for (unsigned b = 0; b < 2; b++) if (contacts[i].body[b])
			{
				// Check for a match with each body in the newly
				// resolved contact
				for (unsigned d = 0; d < 2; d++)
				{
					if (contacts[i].body[b] == contacts[index].body[d])
					{
						deltaPosition = linearChange[d] +
							angularChange[d].cross( contacts[i].relativeContactPosition[b]);

						contacts[i].penetration += deltaPosition.dot(contacts[i].contactNormal) * (b ? 1 : -1);
					}
				}
			}
		}
		positionIterationsUsed++;
	}
}



