#include "AggregateGameObject.h"
#include "../PhysicsEngine/PhysicsManager.h"

string AggregateGameObject::createConnection(string first, string second, ConnectionType type)
{
	// Generate name for connection
	string name = first + "-" + second;

	// Return if unable to add connection
	if (m_connections.containsKey(name)) return "";

	// Create connection
	GameObjectConnection connection;
	connection.m_first = first;
	connection.m_second = second;
	connection.m_type = type;

	// register needed elements in managers
	mp_PhysicsManager->addConnection(name, connection);

	return "";
}




