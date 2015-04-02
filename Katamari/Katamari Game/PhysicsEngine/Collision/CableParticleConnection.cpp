#include "CableParticleConnection.h"
#include "ParticleContact.h"

int CableParticleConnection::AddContact(PhysicsManager* manager)
{
	float length = getCurrentLength();

	// Do nothing if length is less than max
	if (length < m_maxLength) return 0;

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