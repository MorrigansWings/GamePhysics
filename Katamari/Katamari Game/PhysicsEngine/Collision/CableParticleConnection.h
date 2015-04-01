#ifndef _CABLE_PARTICLE_CONNECTION_
#define _CABLE_PARTICLE_CONNECTION_

#include "ParticleConnection.h"

class CableParticleConnection
	: public ParticleConnection
{
public:

	virtual int AddContact(PhysicsManager* manager);

	float	m_maxLength,
			m_restitution;
};

#endif //_CABLE_PARTICLE_CONNECTION_