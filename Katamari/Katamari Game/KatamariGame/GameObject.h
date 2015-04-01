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

	void init(string particle, string entity);

	virtual void update();

	inline string getParticleName() { return m_particleName; }
	inline void setParticleName(string name) { m_particleName = name; }

	inline string getEntityName() { return m_entityName; }
	inline void setEntityName(string name) { m_entityName = name; }

	void applyGravity(){ mp_PhysicsManager->applyGravity(m_particleName); }

	inline Physics::Vector3 getPosition() { return m_position; }
	inline void setPosition(Physics::Vector3 newPos) { m_position = newPos; }

private:
	string m_particleName;
	string m_entityName;

	Physics::Vector3 m_position;
	
};

#endif //_GAME_OBJECT_