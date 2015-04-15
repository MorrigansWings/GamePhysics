#ifndef _GROUND_CONTACT_GENERATOR_
#define _GROUND_CONTACT_GENERATOR_

#include "ParticleContactGenerator.h"

class GroundContactGenerator
	: public ParticleContactGenerator
{
public:
	GroundContactGenerator() { m_groundHeight = 0.0f; }
	~GroundContactGenerator(){}

	virtual int AddContact(PhysicsManager* manager);

	inline float	getGroundHeight() { return m_groundHeight; }
	inline void		setGroundHeight(float height) { m_groundHeight = height; }

private:
	float m_groundHeight;

};

#endif //_GROUND_CONTACT_GENERATOR_