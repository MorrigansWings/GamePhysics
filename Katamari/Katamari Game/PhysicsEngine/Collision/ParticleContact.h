#ifndef _PARTICLE_CONTACT_
#define _PARTICLE_CONTACT_

#include "../Particle.h"

class ParticleContact
{
public:
	ParticleContact(Particle* f, float rest, Vector3 cn, float penetration);
	ParticleContact(Particle* f, Particle* s, float rest, Vector3 cn, float penetration);
	~ParticleContact();


	void resolve(float duration);
	float separatingVelocity() const;	
	
	// GETTERS AND SETTERS
	Particle* getFirstParticle() { return first; }
	Particle* getSecondParticle() { return second; }
	Vector3 getContactNormal() { return contactNormal; }
	float getRestitution() { return restitution; }
	float getPenetrationDepth() { return penetrationDepth; }

	void setFirstParticle(Particle* f) { first = f; }
	void setSecondParticle(Particle* s) { second = s; }
	void setContactNormal(Vector3 norm) { contactNormal = norm; }
	void setRestitution(float rest) { restitution = rest; }
	void setPenetrationDepth(float pen) { penetrationDepth = pen; }
	
private:
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);

	Particle*	first;
	Particle*	second;

	float		restitution;

	Vector3		contactNormal;

	float		penetrationDepth;

};

#endif //_PARTICLE_CONTACT_