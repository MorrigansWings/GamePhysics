#ifndef _AGGREGATE_GAME_OBJECT_
#define _AGGREGATE_GAME_OBJECT_

#include "GameObject.h"
//#include "GameObjectConnection.h"

//class GameObjectConnection;

class AggregateGameObject
	: public GameObject
{
public:
	AggregateGameObject(){}
	~AggregateGameObject(){}

	inline void addGameObject(string name, GameObject* object) { if(!m_objects.containsKey(name)) m_objects[name] = object; }
	inline GameObject* getGameObject(string name) { return m_objects.containsKey(name) ? m_objects[name] : nullptr; }

	string createConnection(string first, string second, ConnectionType type);

	void translate(Physics::Vector3 addPos);

private:
	// Map keeping particles and entities for 
	Arc::Map<string, GameObject*> m_objects;

	Arc::Map<string, GameObjectConnection> m_connections;

};

#endif //_AGGREGATE_GAME_OBJECT_