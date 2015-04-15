#include "RodParticleConnection.h"
#include "ParticleContact.h"

int RodParticleConnection::AddContact(PhysicsManager* manager)
{
	float length = getCurrentLength();

	// Disregard anything past 2nd decimal place
	float checkLength = length;
	checkLength = floorf(length * 100.0f) / 100.0f;

	if (checkLength == m_maxLength) return 0;

	// particle links
	ParticleContact* contact = new ParticleContact();
	contact->setFirstParticle(mp_first);
	contact->setSecondParticle(mp_second);

	// contact normal and penetration depth
	Vector3 normal = mp_second->getPosition() - mp_first->getPosition();
	normal.normalize();
	if (length > m_maxLength)
	{
		contact->setContactNormal(normal);
		contact->setPenetrationDepth(length - m_maxLength);
	}
	else
	{
		contact->setContactNormal(normal * -1.0f);
		contact->setPenetrationDepth(m_maxLength - length);
	}

	// restitution
	contact->setRestitution(0.0f);

	manager->addContact(contact);

	return 1;
}