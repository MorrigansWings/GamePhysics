#ifndef _ROD_PARTICLE_CONNECTION_
#define _ROD_PARTICLE_CONNECTION_

#include "ParticleConnection.h"

class RodParticleConnection
	: public ParticleConnection
{
public:
	virtual int AddContact(PhysicsManager* manager);

	inline void setMaxLength(float length) { m_maxLength = floorf(length * 100.0f) / 100.0f; }

private:
	float m_maxLength;

};

#endif //_ROD_PARTICLE_CONNECTION_