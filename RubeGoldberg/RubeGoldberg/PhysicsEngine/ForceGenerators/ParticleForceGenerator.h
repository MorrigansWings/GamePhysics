#ifndef _PARTICLE_FORCE_GENERATOR_H_
#define _PARTICLE_FORCE_GENERATOR_H_

#pragma once
#include "../Particle.h"

class ParticleForceGenerator 
{
public:
	virtual void updateForce(Particle* particle, float duration) = 0;
};

#endif //_PARTICLE_FORCE_GENERATOR_H_