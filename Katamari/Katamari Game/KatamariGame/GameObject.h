#ifndef _GAME_OBJECT_
#define _GAME_OBJECT_

#include "Object.h"

class GameObject
	: public Object
{
public:
	GameObject(){};
	~GameObject(){};

	void init(string particle, string entity);

	virtual void update();

	string getParticleName() { return m_particleName; }
	void setParticleName(string name) { m_particleName = name; }

	string getEntityName() { return m_entityName; }
	void setEntityName(string name) { m_entityName = name; }

	void applyGravity(){ mp_PhysicsManager->applyGravity(m_particleName); }


private:
	string m_particleName;
	string m_entityName;
	
};

#endif //_GAME_OBJECT_