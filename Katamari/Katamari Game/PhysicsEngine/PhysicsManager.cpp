#include "PhysicsManager.h"

PhysicsManager::PhysicsManager()
{

}

PhysicsManager::~PhysicsManager()
{
	particleSet.clear();
	particleForceRegistry.clear();
	force_registrations_.clear();
}

void PhysicsManager::updateForces(float duration)
{
	Registry::iterator it = force_registrations_.begin();
	for (; it != force_registrations_.end(); ++it)
	{
		it->generator->updateForce(it->particle, duration);
	}
}