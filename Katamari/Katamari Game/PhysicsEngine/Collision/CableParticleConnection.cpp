#include "CableParticleConnection.h"
#include "ParticleContact.h"

int CableParticleConnection::AddContact(PhysicsManager* manager)
{
	float length = getCurrentLength();

	// Disregard anything past 2nd decimal place
	float checkLength = length;
	//checkLength = floorf(length * 100.0f) / 100.0f;	

	// Do nothing if length is less than max
	if (checkLength < m_maxLength) return 0;

	ParticleContact* contact = new ParticleContact();
	contact->setFirstParticle(mp_first);
	contact->setSecondParticle(mp_second);

	Vector3 normal = mp_second->getPosition() - mp_first->getPosition();
	contact->setContactNormal(normal.normalize());

	contact->setPenetrationDepth(length - m_maxLength);

	contact->setRestitution(m_restitution);

	manager->addContact(contact);
	return 1;
}