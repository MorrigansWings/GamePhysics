#include "RigidBodyObject.h"

#include <iostream>

void RigidBodyObject::init(string name, string rigidBody, string entity)
{
	m_name = name;

	if (mp_PhysicsManager->hasRigidBody(rigidBody))
		m_rigidBodyName = rigidBody;

	if (mp_GraphicsManager->hasEntity(entity))
		m_entityName = entity;

	m_position = mp_PhysicsManager->getRigidBodyPosition(m_rigidBodyName);
}

void RigidBodyObject::update()
{
	m_position = mp_PhysicsManager->getRigidBodyPosition(m_rigidBodyName);
	m_orientation = mp_PhysicsManager->getRigidBodyOrientation(m_rigidBodyName);

	mp_GraphicsManager->updateEntityPosition(m_entityName, m_position.GLM());
	mp_GraphicsManager->updateEntityOrientation(m_entityName, Physics::Matrix4::getRotationMatrix(m_orientation.ToMatrix()).GLM());
}