#ifndef _PARTICLE_CONTACT_GENERATOR_
#define _PARTICLE_CONTACT_GENERATOR_

#include "../PhysicsManager.h"

class ParticleContactGenerator
{
public:
	virtual int AddContact(PhysicsManager* manager) = 0;

};


#endif //_PARTICLE_CONTACT_GENERATOR_