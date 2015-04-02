#include <iostream>

#include "GameObject.h"

using namespace Physics;

void GameObject::init(string name, string particle, string entity)
{
	m_name = name;

	if (mp_PhysicsManager->hasParticle(particle))
		m_particleName = particle;

	if (mp_GraphicsManager->hasEntity(entity))
		m_entityName = entity;

	m_position = mp_PhysicsManager->getParticlePosition(m_particleName);
}

void GameObject::update()
{
	// get data from physics engine
	m_position = mp_PhysicsManager->getParticlePosition(m_particleName);
	//std::cout << "GAMEOBJECT:: update(): Attempting to update particle " << m_particleName << " with physics postion: " << newPos.ToString() << std::endl;

	// give data to graphics engine
	mp_GraphicsManager->updateEntityPosition(m_entityName, m_position.GLM());

	//std::cout << "GAMEOBJECT:: update(): " << m_particleName << "'s position after update: " << newPos.ToString() << std::endl;
}