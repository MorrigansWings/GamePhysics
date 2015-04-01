#ifndef _PARTICLE_CONNECTION_
#define _PARTICLE_CONNECTION_

#include "ParticleContactGenerator.h"

class ParticleConnection
	: public ParticleContactGenerator
{
public:

	virtual int AddContact(PhysicsManager* manager) = 0;

	Particle*	mp_first,
				mp_second;
};
#endif //_PARTICLE_CONNECTION_