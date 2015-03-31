#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_

#pragma once
#include <vector>

#include "Particle.h"
#include "ForceGenerators/ParticleForceGenerator.h"
#include "Collision/ParticleContact.h"
#include "Arc/ManagedObject.h"

struct ForceRegistration
{
	Particle *particle;
	ParticleForceGenerator *generator;
};

class PhysicsManager
{
public:
	static PhysicsManager* GetInstance(void) { return s_Instance; }

	PhysicsManager();
	~PhysicsManager();

	void update(float duration);

	void updateForces(float duration);

private:
	static PhysicsManager* s_Instance;

	// Particle Set and Registry
	std::vector<Particle> particleSet;
	std::vector<ParticleForceGenerator*> particleForceRegistry;

	// Contact Set
	std::vector<ParticleContact> contacts;

	// Force Generators
	typedef std::vector<ForceRegistration> Registry;
	Registry force_registrations_;

};

#endif //_PHYSICS_MANAGER_H_