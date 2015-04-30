#ifndef _RIGID_BODY_OBJECT_H_
#define _RIGID_BODY_OBJECT_H_

#include "Object.h"

class RigidBodyObject : public Object
{
public:
	RigidBodyObject(){};
	~RigidBodyObject(){};

	void init(string name, string rigidBody, string entity);

	virtual void update();
	virtual void applyGravity(){ mp_PhysicsManager->applyRigidBodyGravity(m_rigidBodyName); }

	inline string getName() { return m_name; }
	inline void setName(string name) { m_name = name; }

	inline string getEntityName() { return m_entityName; }
	inline void setEntityName(string name) { m_entityName = mp_GraphicsManager->hasEntity(name) ? name : m_entityName; }

	inline string getRigidBodyName() { return m_rigidBodyName; }
	inline void setRigidBodyName(string name) { m_rigidBodyName = mp_PhysicsManager->hasRigidBody(name) ? name : m_rigidBodyName; }

	inline string getColliderName() { return m_colliderName; }
	inline void setColliderName(string name) { m_colliderName = mp_PhysicsManager->hasCollider(name) ? name : m_colliderName; }

	inline Physics::Vector3 getPosition() { return m_position; }
	inline void setPosition(Physics::Vector3 newPos) { m_position = newPos; }

	inline Physics::Quaternion getOrientation() { return m_orientation; }
	inline void setOrientation(Physics::Quaternion newOrient) { m_orientation = newOrient; }

private:
	string m_name;
	string m_entityName; // name of graphics object
	string m_rigidBodyName; // name of physics object
	string m_colliderName; // name of collision primitive for object

	Physics::Vector3 m_position;
	Physics::Quaternion m_orientation;

};

#endif //_RIGID_BODY_OBJECT_H_