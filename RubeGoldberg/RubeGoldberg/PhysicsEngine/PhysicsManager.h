#ifndef _PHYSICS_MANAGER_H_
#define _PHYSICS_MANAGER_H_

#include <vector>
#include <iostream>
#include <Arc/Map.h>

#include "Particle.h"
#include "RigidBody.h"
#include "Collision/CollisionPrimitive.h"
#include "Collision/CollisionDetection_Narrow.h"

class ParticleContact;
class ParticleForceGenerator;
class ParticleContactGenerator;

class RigidBodyContact;
class RigidBodyForceGenerator;
class RigidBodyContactGenerator;

struct ForceRegistration
{
	Particle *particle;
	ParticleForceGenerator *generator;
};

struct RigidBodyForceRegistration
{
	RigidBody *body;
	RigidBodyForceGenerator *generator;
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
	void updateRigidBodyForces(float duration);
	void integrateParticles(float duration);
	void integrateRigidBodies(float duration);
	void generateCollisions();
	void generateRigidBodyCollisions();
	void generateRigidBodyObjectCollisions();
	void generateRigidBodyGroundCollisions();
	void resolveCollisions(float duration);
	void resolveRigidBodyCollisions(float duration);

	void singlePassCollisions(float duration);
	void multiPassCollisions(float duration);

	string createParticle(string name);
	string createParticle(string name, Physics::Vector3 pos);

	Particle* getParticle(string name) { return hasParticle(name) ? m_particleSet[name] : nullptr; }
	Physics::Vector3 getParticlePosition(string &name) { return hasParticle(name) ? m_particleSet[name]->getPosition() : Physics::Vector3(0); }
	bool hasParticle(string &name) { return m_particleSet.containsKey(name); }
	Arc::ArrayList<Particle*> getParticles() { return m_particleSet.getValues(); }

	string createRigidBody(string &name);
	string createRigidBody(string &name, Physics::Vector3 pos);
	string createRigidBody(string &name, Physics::Vector3 pos, Physics::Quaternion orient);

	RigidBody* getRigidBody(string name) { return hasRigidBody(name) ? m_rigidBodySet[name] : nullptr; }
	Physics::Vector3 getRigidBodyPosition(string &name) { return hasRigidBody(name) ? m_rigidBodySet[name]->getPosition() : Physics::Vector3(0); }
	Physics::Quaternion getRigidBodyOrientation(string &name) { return hasRigidBody(name) ? m_rigidBodySet[name]->getOrientation() : Physics::Quaternion(); }
	bool hasRigidBody(string &name) { return m_rigidBodySet.containsKey(name); }
	Arc::ArrayList<RigidBody*> getRigidBodies() { return m_rigidBodySet.getValues(); }

	bool applyGravity(string &name);
	bool applyRigidBodyGravity(string &name);

	void addContact(ParticleContact* cont) { m_contacts.add(cont); }

	string addConnection(string &name, string first, string second, ConnectionType type);
	string addRod(string &name, string first, string second);
	string addCable(string &name, string first, string second);
	string addSpring(string &name, string particle, string anchor);

	bool hasCollider(string &name) { return m_colliders.containsKey(name); }
	string addCollisionSphere(string &name, string &bodyName);
	string addCollisionSphere(string &name, string &bodyName, float radius);
	string addCollisionBox(string &name, string &bodyName);
	string addCollisionBox(string &name, string &bodyName, Physics::Vector3 halfSize);

private:
	static PhysicsManager* s_Instance;
	const static unsigned MAX_CONTACTS = 256;

	// Particle code! ==================================================
	// Particle Set and Registry
	Arc::Map<string, Particle*> m_particleSet;
	Arc::Map<string, ParticleForceGenerator*> m_particleForceRegistry;

	// Force Generators
	//typedef std::vector<ForceRegistration> Registry;
	Arc::ArrayList<ForceRegistration> m_forceRegistrations;

	// Contact Set
	Arc::Map<string, ParticleContactGenerator*> m_particleContactRegistry;
	Arc::ArrayList<ParticleContact*> m_contacts;

	// Rigid Body code! ==================================================
	// Rigid Body Set, Collision Primitive set, and Registry
	Arc::Map<string, RigidBody*> m_rigidBodySet;
	Arc::Map<string, CollisionPrimitive*> m_colliders;
	Arc::Map<string, RigidBodyForceGenerator*> m_rigidBodyForceRegistry;

	// Rigid Body Force Generators
	Arc::ArrayList<RigidBodyForceRegistration> m_rigidBodyForceRegistrations;

	// Rigid Body Contacts
	//Arc::Map<string, RigidBodyContactGenerator*> m_rigidBodyContactRegistry;
	//Arc::ArrayList<RigidBodyContact*> m_rigidBodyContacts;
	Contact m_rigidBodyContacts[MAX_CONTACTS];
	CollisionData m_data;
	ContactResolver* mp_contactResolver;

	CollisionPlane* mp_groundCollisionPlane;

	float	m_groundHeight,
			m_groundXBounds,
			m_groundYBounds;

	int m_maxPasses;

};

#endif //_PHYSICS_MANAGER_H_