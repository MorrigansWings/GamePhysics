#ifndef _PARTICLE_CONTACT_
#define _PARTICLE_CONTACT_

#include "../Particle.h"

class ParticleContact
{
public:
	ParticleContact(){};
	ParticleContact(Particle* f, float rest, Vector3 cn, float penetration)
		: m_first(f)
		, m_second(nullptr)
		, m_restitution(rest)
		, m_contactNormal(cn)
		, m_penetrationDepth(penetration)
	{}
	ParticleContact(Particle* f, Particle* s, float rest, Vector3 cn, float penetration)
		: m_first(f)
		, m_second(s)
		, m_restitution(rest)
		, m_contactNormal(cn)
		, m_penetrationDepth(penetration)
	{}
	~ParticleContact(){};

	void resolve(float duration);
	float separatingVelocity() const;	
	
	// GETTERS AND SETTERS
	Particle* getFirstParticle() { return m_first; }
	Particle* getSecondParticle() { return m_second; }
	Vector3 getContactNormal() { return m_contactNormal; }
	float getRestitution() { return m_restitution; }
	float getPenetrationDepth() { return m_penetrationDepth; }

	void setFirstParticle(Particle* f) { m_first = f; }
	void setSecondParticle(Particle* s) { m_second = s; }
	void setContactNormal(Vector3 norm) { m_contactNormal = norm; }
	void setRestitution(float rest) { m_restitution = rest; }
	void setPenetrationDepth(float pen) { m_penetrationDepth = pen; }
	
private:
	void resolveVelocity(float duration);
	void resolveInterpenetration(float duration);

	Particle*	m_first;
	Particle*	m_second;
				
	float		m_restitution;
				
	Vector3		m_contactNormal;
				
	float		m_penetrationDepth;

};

#endif //_PARTICLE_CONTACT_