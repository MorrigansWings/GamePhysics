#include "PhysicsManager.h"

PhysicsManager* PhysicsManager::s_Instance = nullptr;

PhysicsManager::PhysicsManager()
{
	s_Instance = this;
}

PhysicsManager::~PhysicsManager()
{
	particleSet.clear();
	particleForceRegistry.clear();
	force_registrations_.clear();
}

void PhysicsManager::update(float duration)
{
	// Clear force accumulators

	// Generate forces via generators

	// Integrate particle positions

	// Compute set of all particles in contact

	// Resolve velocities for all particles in contact

	// Resolve interpenetration for all particles in contact
}


void PhysicsManager::updateForces(float duration)
{
	Registry::iterator it = force_registrations_.begin();
	for (; it != force_registrations_.end(); ++it)
	{
		it->generator->updateForce(it->particle, duration);
	}
}