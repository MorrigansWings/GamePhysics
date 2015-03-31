#ifndef _BUNGEE_FORCE_GENERATOR_
#define _BUNGEE_FORCE_GENERATOR_

#include "ParticleForceGenerator.h"
#include "../Vectors.h"

class BungeeForceGenerator : public ParticleForceGenerator
{
public:
	BungeeForceGenerator();
	~BungeeForceGenerator();

	virtual void updateForce(Particle* particle, float duration);

private:
	Particle*	mEndPosition;
	const float mK = 1.0f;
	const float mRestLength = 1.0f;
};

#endif //_BUNGEE_FORCE_GENERATOR_