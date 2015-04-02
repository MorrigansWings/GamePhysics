#ifndef _ROD_PARTICLE_CONNECTION_
#define _ROD_PARTICLE_CONNECTION_

#include "ParticleConnection.h"

class RodParticleConnection
	: public ParticleConnection
{
public:
	virtual int AddContact(PhysicsManager* manager);

	float m_maxLength;

};

#endif //_ROD_PARTICLE_CONNECTION_