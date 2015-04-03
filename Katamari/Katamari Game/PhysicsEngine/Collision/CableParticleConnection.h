#ifndef _CABLE_PARTICLE_CONNECTION_
#define _CABLE_PARTICLE_CONNECTION_

#include "ParticleConnection.h"

class CableParticleConnection
	: public ParticleConnection
{
public:

	virtual int AddContact(PhysicsManager* manager);

	inline void setMaxLength(float mLength){ m_maxLength = floorf(mLength * 100.0f) / 100.0f; }
	inline void setRestitution(float rest) { m_restitution = rest; }

private:
	float	m_maxLength,
			m_restitution;
};

#endif //_CABLE_PARTICLE_CONNECTION_