#include "ParticleContact.h"

ParticleContact::ParticleContact(Particle* f, float rest, Vector3 cn, float penetration)
{

}

ParticleContact::ParticleContact(Particle* f, Particle* s, float rest, Vector3 cn, float penetration)
{

}

ParticleContact::~ParticleContact()
{}

void ParticleContact::resolve(float duration)
{
	// update velocity on both particles
	resolveVelocity(duration);

	// update positions to resolve interpenetration
}

float ParticleContact::separatingVelocity() const
{
	Vector3 relativeVelocity = first->getVelocity();
	if (second != NULL)
	{
		relativeVelocity -= second->getVelocity();
	}

	return relativeVelocity.dot(contactNormal);
}

// NOTE :: ADJUST FOR NULL PARTICLE B!!!
void ParticleContact::resolveVelocity(float duration)
{
	float separating = separatingVelocity();
	if (separating > 0)
		return;
	float newVel = -restitution * separating;
	float totalMass = first->getMass() + second->getMass();
	//if (second != NULL)
	//	totalMass += second->getMass();
	float deltaVel = newVel - separating;
	float impulseMag = deltaVel / totalMass;
	Vector3 impulse = contactNormal * impulseMag;
	first->setVelocity(first->getVelocity() + (impulse * second->getMass()));
	second->setVelocity(second->getVelocity() - (impulse * first->getMass()));
}

void ParticleContact::resolveInterpenetration(float duration)
{
	if (penetrationDepth <= 0) return;
	float totalMass = first->getMass();
	if (second != NULL)
		totalMass += second->getMass();
	Vector3 displacement = contactNormal * penetrationDepth / totalMass;

	Vector3 firstMove = displacement * second->getMass();
	Vector3 secondMove = displacement * first->getMass();
	first->setPosition(first->getPosition() + firstMove);
	second->setPosition(second->getPosition() - secondMove);

}