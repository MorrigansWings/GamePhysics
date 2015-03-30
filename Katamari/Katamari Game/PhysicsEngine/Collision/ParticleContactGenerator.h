#ifndef _PARTICLE_CONTACT_GENERATOR_
#define _PARTICLE_CONTACT_GENERATOR_

class ParticleContactGenerator
{
public:
	virtual int AddContact(ParticleSimulation &simulation) = 0;

};


#endif //_PARTICLE_CONTACT_GENERATOR_