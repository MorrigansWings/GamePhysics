#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_

#pragma once
#include <vector>

#include "Particles/Particle.h"
#include "Particles/ParticleForceGenerator.h"

struct ForceRegistration
{
	Particle *particle;
	ParticleForceGenerator *generator;
};

class PhysicsManager
{
public:
	PhysicsManager();
	~PhysicsManager();

	void updateForces(float duration);

private:
	// Particle Set and Registry
	std::vector<Particle> particleSet;
	std::vector<ParticleForceGenerator*> particleForceRegistry;

	// Contact Set

	// Force Generators
	typedef std::vector<ForceRegistration> Registry;
	Registry force_registrations_;

};

#endif //_PHYSICS_MANAGER_H_