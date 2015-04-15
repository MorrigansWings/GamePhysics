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

	updateLines();
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
	string connectionName = mp_PhysicsManager->addConnection(name, first->getParticleName(), second->getParticleName(), type);
	m_connections.add(connectionName, connection);

	// Create graphical line
	//std::cout << "AGGREGATEGAMEOBJECT:drawLines: Attempting to draw line from "
	//	<< first->getPosition().ToString() << " to "
	//	<< second->getPosition().ToString() << std::endl;
	m_lines.add(connectionName, mp_GraphicsManager->createLine(connectionName + "_line", first->getPosition().GLM(), second->getPosition().GLM()));

	return name;
}

void AggregateGameObject::updateLines()
{
	//std::cout << "AGGREGATEGAMEOBJECT::updateLines: Starting for loop in updateLines..." << std::endl;
	for (auto iter = m_lines.itBegin(); iter != m_lines.itEnd(); ++iter)
	{
		GameObject* first = m_connections[iter->first].m_first;
		GameObject* second = m_connections[iter->first].m_second;

		mp_GraphicsManager->removeEntity(iter->second);
	}

	for (auto iter = m_connections.itBegin(); iter != m_connections.itEnd(); ++iter)
	{
		GameObject* first = iter->second.m_first;
		GameObject* second = iter->second.m_second;

		m_lines.add(iter->first, mp_GraphicsManager->createLine(iter->first, first->getPosition().GLM(), second->getPosition().GLM()));
	}
}


