#ifndef _GRAVITY_FORCE_GENERATOR_
#define _GRAVITY_FORCE_GENERATOR_
#pragma once

#include "ParticleForceGenerator.h"
#include "../Vectors.h"

class GravityForceGenerator : ParticleForceGenerator
{
public:
	static float GRAVITATIONAL_CONSTANT; // Gravitational Constant
	static float GAUSSIAN_CONSTANT; // Gravitational Constant for AU

	GravityForceGenerator();
	~GravityForceGenerator();

	virtual void updateForce(Particle* particle, float duration);


private:
	Vector3 gravity;

};

#endif //_GRAVITY_FORCE_GENERATOR_