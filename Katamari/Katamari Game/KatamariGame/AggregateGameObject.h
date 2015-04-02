#ifndef _AGGREGATE_GAME_OBJECT_
#define _AGGREGATE_GAME_OBJECT_

#include "GameObject.h"
//#include "GameObjectConnection.h"

//class GameObjectConnection;

struct GameObjectConnection
{
	GameObject* m_first;
	GameObject* m_second;
	ConnectionType m_type;
};

class AggregateGameObject
	: public GameObject
{
public:
	AggregateGameObject(){}
	~AggregateGameObject(){}

	virtual void update();
	virtual void applyGravity();

	inline void addGameObject(string name, GameObject* object) { if(!m_objects.containsKey(name)) m_objects[name] = object; }
	inline GameObject* getGameObject(string name) { return m_objects.containsKey(name) ? m_objects[name] : nullptr; }

	string createConnection(GameObject* first, GameObject* second, ConnectionType type);

	void translate(Physics::Vector3 addPos);

private:
	// Map keeping particles and entities for 
	Arc::Map<string, GameObject*> m_objects;

	Arc::Map<string, GameObjectConnection> m_connections;

};

#endif //_AGGREGATE_GAME_OBJECT_