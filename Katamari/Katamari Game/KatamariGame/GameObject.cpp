#include <iostream>

#include "GameObject.h"

using namespace Physics;

void GameObject::init(string particle, string entity)
{
//	if (mp_PhysicsManager->hasParticle(particle))
		m_particleName = particle;

//	if (mp_GraphicsManager->hasEntity(entity))
		m_entityName = entity;
}

void GameObject::update()
{
	// get data from physics engine
	Physics::Vector3 newPos = mp_PhysicsManager->getParticlePosition(m_particleName);
	std::cout << "GAMEOBJECT:: update(): Attempting to update particle " << m_particleName << " with physics postion: " << newPos.ToString() << std::endl;

	// give data to graphics engine
	mp_GraphicsManager->updateEntityPosition(m_entityName, newPos.convertToGLM());
}