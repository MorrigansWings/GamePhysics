#ifndef _OBJECT_
#define _OBJECT_

#include "../GraphicsEngine/GraphicsManager.h"
#include "../PhysicsEngine/PhysicsManager.h"

#include "../PhysicsEngine/Vectors.h"

using namespace Physics;

class Object
{
public:
	virtual void update() = 0;

	inline Physics::Vector3 getPosition() { return m_position; }
	inline void	setPosition(Physics::Vector3 pos) { m_position = pos; }

	void setGraphicsManager(GraphicsManager* gm) { mp_GraphicsManager = gm; }
	void setPhysicsManager(PhysicsManager* pm) { mp_PhysicsManager = pm; }

protected:
	GraphicsManager*	mp_GraphicsManager;
	PhysicsManager*		mp_PhysicsManager;

	Physics::Vector3 m_position;
};

#endif //_OBJECT_