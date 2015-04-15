#ifndef _PARTICLE_CONNECTION_
#define _PARTICLE_CONNECTION_

#include "ParticleContactGenerator.h"

class ParticleConnection
	: public ParticleContactGenerator
{
public:

	virtual int AddContact(PhysicsManager* manager) = 0;

	inline float getCurrentLength(){ return Vector3::getDistance(mp_first->getPosition(), mp_second->getPosition()); }
	
	Particle*	mp_first;
	Particle*	mp_second;
};
#endif //_PARTICLE_CONNECTION_