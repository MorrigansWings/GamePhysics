#include "AggregateGameObject.h"
#include "../PhysicsEngine/PhysicsManager.h"

void AggregateGameObject::update()
{
	// Cycle through objects
	for (auto iter = m_objects.itBegin(); iter != m_objects.itEnd(); ++iter)
	{
		// get data from physics engine
		Physics::Vector3 m_position;
		m_position = mp_PhysicsManager->getParticlePosition(iter->second->getParticleName());
		//std::cout << "GAMEOBJECT:: update(): Attempting to update particle " << m_particleName << " with physics postion: " << newPos.ToString() << std::endl;

		// give data to graphics engine
		mp_GraphicsManager->updateEntityPosition(iter->second->getEntityName(), m_position.GLM());
	}
}

void AggregateGameObject::applyGravity()
{
	// Cycle through objects
	for (auto iter = m_objects.itBegin(); iter != m_objects.itEnd(); ++iter)
	{
		mp_PhysicsManager->applyGravity(iter->second->getParticleName());
	}
}

string AggregateGameObject::createConnection(GameObject* first, GameObject* second, ConnectionType type)
{
	// Generate name for connection
	string name = first->getName() + "-" + second->getName();

	// Return if unable to add connection
	if (m_connections.containsKey(name)) return "";

	// Create connection
	GameObjectConnection connection;
	connection.m_first = first;
	connection.m_second = second;
	connection.m_type = type;

	// register needed elements in managers
	mp_PhysicsManager->addConnection(name, first->getParticleName(), second->getParticleName(), type);

	return name;
}




