#include "ParticleContact.h"

void ParticleContact::resolve(float duration)
{
	// update velocity on both particles
	resolveVelocity(duration);

	// update positions to resolve interpenetration
	resolveInterpenetration(duration);
}

float ParticleContact::separatingVelocity() const
{
	Vector3 relativeVelocity = m_first->getVelocity();
	if (m_second != nullptr)
	{
		relativeVelocity -= m_second->getVelocity();
	}

	return relativeVelocity.dot(m_contactNormal);
}

void ParticleContact::resolveVelocity(float duration)
{
	// separating velocity calculations
	float separating = separatingVelocity();
	if (separating > 0) return;
	float newSeparatingVel = -m_restitution * separating;

	// Check for velocity buildup due to acceleration
	Vector3 acceleration = m_first->getAcceleration();
	if (m_second != nullptr)
		acceleration -= m_second->getAcceleration();
	float accelSepVelocity = Vector3::dot(acceleration, m_contactNormal) * duration;

	if (accelSepVelocity < 0)
	{
		newSeparatingVel += m_restitution * accelSepVelocity;
		if (newSeparatingVel < 0)
			newSeparatingVel = 0.0f;
	}

	// Calculate change in separating velocity
	float deltaVel = newSeparatingVel - separating;

	// mass calculations
	float totalInverseMass = m_first->getInverseMass();
	if (m_second != nullptr)
		totalInverseMass += m_second->getInverseMass();
	if (totalInverseMass <= 0) return;
	
	// impulse calculation	
	float impulseMag = deltaVel / totalInverseMass;
	
	// impulse per unit of inverse mass
	Vector3 impulse = m_contactNormal * impulseMag;

	m_first->setVelocity(m_first->getVelocity() + (impulse * m_first->getInverseMass()));
	if (m_second != nullptr) // if second particle exists, apply!
		m_second->setVelocity(m_second->getVelocity() - (impulse * m_second->getInverseMass()));
}

void ParticleContact::resolveInterpenetration(float duration)
{
	// if none, skip function
	if (m_penetrationDepth <= 0) return;


	float totalInverseMass = m_first->getInverseMass();
	if (m_second != nullptr)
		totalInverseMass += m_second->getInverseMass();
	if (totalInverseMass <= 0) return;
//	float totalMass = m_first->getMass();
//	if (m_second != nullptr)
//		totalMass += m_second->getMass();
//	Vector3 displacement = m_contactNormal * m_penetrationDepth / totalMass;

	// amount of penetration resolution per unit of inverse mass
	Vector3 movePerInverseMass = m_contactNormal * (m_penetrationDepth / totalInverseMass);

	// Calculate amounts per particle
	Vector3 firstMove = movePerInverseMass * m_first->getInverseMass();
	Vector3 secondMove = (m_second != nullptr) ? movePerInverseMass * m_second->getInverseMass() : Vector3(0);

	m_first->setPosition(m_first->getPosition() + firstMove);
	if (m_second != nullptr)
		m_second->setPosition(m_second->getPosition() - secondMove);

}