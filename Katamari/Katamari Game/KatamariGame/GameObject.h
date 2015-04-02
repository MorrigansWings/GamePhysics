#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include "Object.h"
#include "../PhysicsEngine/Vectors.h"

class GameObject
	: public Object
{
public:
	GameObject(){};
	~GameObject(){};

	void init(string name, string particle, string entity);

	virtual void update();
	virtual void applyGravity(){ mp_PhysicsManager->applyGravity(m_particleName); }

	inline string getParticleName() { return m_particleName; }
	inline void setParticleName(string name) { m_particleName = name; }

	inline string getEntityName() { return m_entityName; }
	inline void setEntityName(string name) { m_entityName = name; }

	inline string getName() { return m_name; }
	inline void setName(string name) { m_name = name; }

	inline Physics::Vector3 getPosition() { return m_position; }
	inline void setPosition(Physics::Vector3 newPos) { m_position = newPos; }

private:
	string m_name;
	string m_particleName;
	string m_entityName;

	Physics::Vector3 m_position;
	
};

#endif //_GAME_OBJECT_