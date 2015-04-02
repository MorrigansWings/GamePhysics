#include "GroundContactGenerator.h"

#include "ParticleContact.h"

int GroundContactGenerator::AddContact(PhysicsManager* manager)
{
	// Cycle through particles...
	Arc::ArrayList<Particle*> particles = manager->getParticles();
	for (unsigned int i = 0; i < particles.getSize(); ++i)
	{
		Particle* current = particles[i];
		if (current->getPosition().y < m_groundHeight)
		{
			float depth = current->getPosition().y - m_groundHeight;
			ParticleContact* contact = new ParticleContact(current, 0.3f, Vector3(0.0f, 1.0f, 0.0f), depth);
			manager->addContact(contact);
		}
	}
	return 0;
}