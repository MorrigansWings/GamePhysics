#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_

#include <vector>
#include <iostream>
#include <Arc/Map.h>

#include "Particle.h"

class ParticleContact;
class ParticleForceGenerator;
class ParticleContactGenerator;

struct ForceRegistration
{
	Particle *particle;
	ParticleForceGenerator *generator;
};

enum ConnectionType
{
	ROD = 0,
	CABLE,
	SPRING
};

class PhysicsManager
{
public:
	static PhysicsManager* GetInstance(void) { return s_Instance; }

	PhysicsManager();
	~PhysicsManager();

	void setupGround(float height, float xbounds, float ybounds);

	void update(float duration);
	void updateForces(float duration);
	void integrateParticles(float duration);
	void generateCollisions();
	void resolveCollisions(float duration);

	void singlePassCollisions(float duration);
	void multiPassCollisions(float duration);

	string createParticle(string name);
	string createParticle(string name, Physics::Vector3 pos);

	Particle* getParticle(string name) { return hasParticle(name) ? m_particleSet[name] : nullptr; }
	Physics::Vector3 getParticlePosition(string &name) { return hasParticle(name) ? m_particleSet[name]->getPosition() : Physics::Vector3(0); }
	bool hasParticle(string &name) { return m_particleSet.containsKey(name); }
	Arc::ArrayList<Particle*> getParticles() { return m_particleSet.getValues(); }

	bool applyGravity(string &name);

	void addContact(ParticleContact* cont) { m_contacts.add(cont); }

	string addConnection(string &name, string first, string second, ConnectionType type);
	string addRod(string &name, string first, string second);
	string addCable(string &name, string first, string second);
	string addSpring(string &name, string particle, string anchor);

private:
	static PhysicsManager* s_Instance;

	// Particle Set and Registry
	Arc::Map<string, Particle*> m_particleSet;
	Arc::Map<string, ParticleForceGenerator*> m_particleForceRegistry;

	// Force Generators
	//typedef std::vector<ForceRegistration> Registry;
	Arc::ArrayList<ForceRegistration> m_forceRegistrations;

	// Contact Set
	Arc::Map<string, ParticleContactGenerator*> m_particleContactRegistry;
	Arc::ArrayList<ParticleContact*> m_contacts;

	float	m_groundHeight,
			m_groundXBounds,
			m_groundYBounds;

	int m_maxPasses;

};

#endif //_PHYSICS_MANAGER_H_