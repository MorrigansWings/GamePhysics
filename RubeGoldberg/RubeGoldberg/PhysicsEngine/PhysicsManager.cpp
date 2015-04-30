#include "PhysicsManager.h"

#include <iostream>

#include "ForceGenerators/ParticleForceGenerator.h"
#include "ForceGenerators/GravityForceGenerator.h"
#include "ForceGenerators/SpringForceGenerator.h"
#include "Collision/ParticleContact.h"
#include "Collision/ParticleContactGenerator.h"
#include "Collision/GroundContactGenerator.h"
#include "Collision/CableParticleConnection.h"
#include "Collision/RodParticleConnection.h"

#include "ForceGenerators/RigidBodyForceGenerator.h"
#include "ForceGenerators/RigidBodyGravityGenerator.h"

PhysicsManager* PhysicsManager::s_Instance = nullptr;

PhysicsManager::PhysicsManager()
{
	s_Instance = this;

	// Set up force generators
	GravityForceGenerator* gravity = new GravityForceGenerator(2.0f); // scale gravity by 2
	m_particleForceRegistry.add("gravity", gravity);

	// Set up force generators for rigid bodies
	RigidBodyGravityGenerator* rbGravity = new RigidBodyGravityGenerator();
	m_rigidBodyForceRegistry.add("gravity", rbGravity);

	mp_contactResolver = new ContactResolver(1);
	m_data.contactArray = m_rigidBodyContacts;
	m_data.contacts = m_rigidBodyContacts;

	m_maxPasses = 10;
}

PhysicsManager::~PhysicsManager()
{
	for (auto iter = m_particleSet.itBegin(); iter != m_particleSet.itEnd(); ++iter)
		delete iter->second;
	m_particleSet.clear();
	
	for (auto iter = m_particleForceRegistry.itBegin(); iter != m_particleForceRegistry.itEnd(); ++iter)
		delete iter->second;
	m_particleForceRegistry.clear();

	m_forceRegistrations.clear();
}

void PhysicsManager::setupGround(float height, float xbounds, float ybounds)
{
	m_groundHeight = height;
	//m_groundXBounds = xbounds; // currently ignored! will be good for planes with edges
	//m_groundYBounds = ybounds; // that you can fall off off

	// create ground collision generator for particles
	GroundContactGenerator* ground = new GroundContactGenerator();
	ground->setGroundHeight(m_groundHeight);
	m_particleContactRegistry.add("ground", ground);

	// Create ground collision plane for rigid body collision
	mp_groundCollisionPlane = new CollisionPlane();
	mp_groundCollisionPlane->direction = Vector3(0.0f, 1.0f, 0.0f);
	mp_groundCollisionPlane->offset = 0.0f;
}

void PhysicsManager::update(float duration)
{
	// Clear force accumulators
	//for (auto iter = m_particleSet.itBegin(); iter != m_particleSet.itEnd(); ++iter)
	//	iter->second->clearAccumulation();
	for (auto iter = m_rigidBodySet.itBegin(); iter != m_rigidBodySet.itEnd(); ++iter)
		iter->second->clearAccumulators();

	// Generate forces via generators
	//updateForces(duration);
	updateRigidBodyForces(duration);

	// Integrate positions
	//integrateParticles(duration);
	integrateRigidBodies(duration);

	// Compute set of all particles in contact
	//generateCollisions();
	generateRigidBodyCollisions();

	//singlePassCollisions(duration);
	//multiPassCollisions(duration);
	std::cout << "RESOLVING CONTACTS! COUNT: " << m_data.contactCount << std::endl;
	mp_contactResolver->resolveContacts(m_rigidBodyContacts, m_data.contactCount, duration);
	
	// clear contacts after resolution
	//for (unsigned int i = 0; i < m_contacts.getSize(); ++i)
	//	m_contacts.removeAt(i);
	//
	//m_contacts.clear();

}

void PhysicsManager::updateForces(float duration)
{
	//for (auto it = m_forceRegistrations.itBegin(); it != m_forceRegistrations.itEnd(); ++it)
	for (unsigned int i = 0; i < m_forceRegistrations.getSize(); ++i)
	{
		//std::cout << "PHYSICSMANAGER:updateForces: Attempting to update generator " << i << std::endl; 
		ParticleForceGenerator* generator = m_forceRegistrations[i].generator;
		Particle* particle = m_forceRegistrations[i].particle;

		generator->updateForce(particle, duration);
	}
}

void PhysicsManager::updateRigidBodyForces(float duration)
{
	for (unsigned int i = 0; i < m_rigidBodyForceRegistrations.getSize(); ++i)
	{
		//std::cout << "PHYSICSMANAGER:updateForces: Attempting to update generator " << i << std::endl; 
		RigidBodyForceGenerator* generator = m_rigidBodyForceRegistrations[i].generator;
		RigidBody* body = m_rigidBodyForceRegistrations[i].body;

		generator->updateForce(body, duration);
	}
}

void PhysicsManager::integrateParticles(float duration)
{
	for (auto iter = m_particleSet.itBegin(); iter != m_particleSet.itEnd(); ++iter)
		iter->second->integrate(duration);
}

void PhysicsManager::integrateRigidBodies(float duration)
{
	for (auto iter = m_rigidBodySet.itBegin(); iter != m_rigidBodySet.itEnd(); ++iter)
		iter->second->integrate(duration);
}

void PhysicsManager::generateCollisions()
{
	for (auto iter = m_particleContactRegistry.itBegin(); iter != m_particleContactRegistry.itEnd(); ++iter)
	{
		//std::cout << "PHYSICSMANAGER:generateCollisions(): Generating collisions with generator: " << iter->first << std::endl;
		iter->second->AddContact(s_Instance);
	}

}

void PhysicsManager::generateRigidBodyCollisions()
{
	// brute force - check everything!

	// Set up collision data structure
	m_data.reset(MAX_CONTACTS);
	m_data.friction = 0.9f;
	m_data.restitution = 0.6f;
	m_data.tolerance = 0.1f;
	
	// Check Spheres first
	for (auto iter = m_colliders.itBegin(); iter != m_colliders.itEnd(); ++iter)
	{
		if (!m_data.hasMoreContacts()) return;
		// Check against ground plane
		CollisionSphere* sphere = iter->second;
		CollisionDetector::sphereAndHalfSpace(*sphere, *mp_groundCollisionPlane, &m_data);
	}
}

void PhysicsManager::resolveCollisions(float duration)
{
	for (unsigned int i = 0; i < m_contacts.getSize(); ++i)
	{
		m_contacts[i]->resolve(duration);
	}

	// clear contacts after resolution...?
	for (unsigned int i = 0; i < m_contacts.getSize(); ++i)
	{
		m_contacts.removeAt(i);
	}
	m_contacts.clear();
}

void PhysicsManager::singlePassCollisions(float duration)
{
	// Resolve velocities for all particles in contact
	resolveCollisions(duration);
}

void PhysicsManager::multiPassCollisions(float duration)
{
	int processed = 0;
	while (processed < m_maxPasses)
	{
		float minSeparatingVelocity = std::numeric_limits<float>::max();
		int candidate = 0;
		for (unsigned int i = 0; i < m_contacts.getSize(); ++i)
		{
			// get collision with greatest velocity
			float separating = m_contacts[i]->separatingVelocity();
			if (separating <= minSeparatingVelocity && (separating < 0.0f || m_contacts[i]->getPenetrationDepth() > 0))
			{
				minSeparatingVelocity = separating;
				candidate = i;
			}
		}
		// no collision found
		if (minSeparatingVelocity > 0.0f)
			return;

		// Get particles involved
		Particle* first = m_contacts[candidate]->getFirstParticle();
		Particle* second = m_contacts[candidate]->getSecondParticle();

		// process best candidate
		std::cout << "PHYSICSMANAGER:multiPassCollisions: Processing candidate #" << std::to_string(candidate) << std::endl;
		m_contacts[candidate]->resolve(duration);

		// Get new positions of particles involved
		Vector3 firstPos = m_contacts[candidate]->getFirstParticle()->getPosition();
		Vector3 secondPos = Vector3(0.0f);
		if (m_contacts[candidate]->getSecondParticle() != nullptr)
			secondPos = m_contacts[candidate]->getSecondParticle()->getPosition();

		// update particle positions in each other contact
		for (unsigned int i = 0; i < m_contacts.getSize(); ++i)
		{
			ParticleContact* contact = m_contacts[i];
			if (contact->getFirstParticle() == first) contact->getFirstParticle()->setPosition(firstPos);
			if (second != nullptr)
				if (contact->getFirstParticle() == second) contact->getFirstParticle()->setPosition(secondPos);

			if (contact->getSecondParticle() != nullptr)
			{
				if (contact->getSecondParticle() == first) contact->getSecondParticle()->setPosition(firstPos);
				if (second != nullptr)
					if (contact->getSecondParticle() == second) contact->getSecondParticle()->setPosition(secondPos);
			}
		}

		++processed;
	}
}

string PhysicsManager::createParticle(string name)
{
	//std::cout << "PHYSICSMANAGER::createParticle(): Attempting to create new particle named " << name << "..." << std::endl;
	if (!m_particleSet.containsKey(name))
	{
		m_particleSet.add(name, new Particle());
		//std::cout << "\tCreated new particle named " << name << std::endl;
		return name;
	}
	else return "";
}

string PhysicsManager::createParticle(string name, Vector3 pos)
{
	//std::cout << "PHYSICSMANAGER::createParticle(): Attempting to create new particle named " << name << " at position : " << pos.ToString() << std::endl;
	if (!m_particleSet.containsKey(name))
	{
		Particle* newpart = new Particle();
		newpart->setPosition(pos);
		m_particleSet.add(name, newpart);
		//std::cout << "\tCreated new particle named " << name << std::endl;
		return name;
	}
	else return "";
}

string PhysicsManager::createRigidBody(string &name)
{
	if (!m_rigidBodySet.containsKey(name))
	{
		m_rigidBodySet.add(name, new RigidBody());
		return name;
	}
	else return "";
}

string PhysicsManager::createRigidBody(string &name, Physics::Vector3 pos)
{
	if (!m_rigidBodySet.containsKey(name))
	{
		RigidBody* newbody = new RigidBody();
		newbody->setPosition(pos);
		m_rigidBodySet.add(name, newbody);
		return name;
	}
	else return "";
}

string PhysicsManager::createRigidBody(string &name, Physics::Vector3 pos, Physics::Quaternion orient)
{
	if (!m_rigidBodySet.containsKey(name))
	{
		RigidBody* newbody = new RigidBody();
		newbody->setPosition(pos);
		newbody->setOrientation(orient);
		newbody->calculateDerivedData();
		m_rigidBodySet.add(name, newbody);
		return name;
	}
	else return "";
}

bool PhysicsManager::applyGravity(string &name)
{
	if (m_particleSet.containsKey(name) && m_particleForceRegistry.containsKey("gravity"))
	{
		ForceRegistration newForce;
		newForce.generator = m_particleForceRegistry["gravity"];
		newForce.particle = m_particleSet[name];
		m_forceRegistrations.add(newForce);
		return true;
	}
	return false;
}

bool PhysicsManager::applyRigidBodyGravity(string &name)
{
	if (m_rigidBodySet.containsKey(name) && m_rigidBodyForceRegistry.containsKey("gravity"))
	{
		RigidBodyForceRegistration newForce;
		newForce.generator = m_rigidBodyForceRegistry["gravity"];
		newForce.body = m_rigidBodySet[name];
		m_rigidBodyForceRegistrations.add(newForce);
		return true;
	}
	return false;
}

string PhysicsManager::addConnection(string &name, string first, string second, ConnectionType type)
{
	//std::cout << "PHYSICSMANAGER::addConnection(): Attempting to add connection " << name << "..." << std::endl;
	//std::cout << "\tChecking for keys ( " << first << ", " << second << ") ..." << std::endl;

	string result = "";
	if (m_particleSet.containsKey(first) && m_particleSet.containsKey(second))
	{
		//std::cout << "\tBoth keys ( " << first << ", " << second << ") found! moving into switch statement..." << std::endl;
		switch (type)
		{
		case ROD:
			// Add only if name doesn't already exist in registry
			if (!m_particleContactRegistry.containsKey(name + "_rod"))
				result = addRod(name + "_rod", first, second);

			break;
		case CABLE:
			// return without adding if contact name already exists
			if (!m_particleContactRegistry.containsKey(name + "_cable"))
					result = addCable(name + "_cable", first, second);

			break;
		case SPRING:
			// return without adding if contact name already exists
			if (! m_particleForceRegistry.containsKey(name + "_spring_first")
				&& ! m_particleForceRegistry.containsKey(name + "_spring_second"))
			{
				//std::cout << "PHYSICSMANAGER:addConnection: Attempting to add spring force generators to registry..." << std::endl;
				// One generator for each side...
				result = addSpring(name + "_spring_first", first, second);
				result += addSpring(name + "_spring_second", second, first);

				if (result != "")
					result = name + "_spring";

			}
			break;
		}
	}
	return result;
}

string PhysicsManager::addRod(string &name, string first, string second)
{
	RodParticleConnection* rod = new RodParticleConnection();

	rod->mp_first = m_particleSet[first];
	rod->mp_second = m_particleSet[second];
	
	// calculate max length
	float mLength = Vector3::getDistance(	rod->mp_first->getPosition(),
											rod->mp_second->getPosition());
	rod->setMaxLength(mLength);

	// Add contact generator to registry
	//std::cout << "PHYSICSMANAGER::addRod(): Adding RodParticleConnection to particleContactRegistry[" << name << "]" << std::endl;
	//m_particleContactRegistry[name] = rod;
	m_particleContactRegistry.add(name, rod);
	return name;
}

string PhysicsManager::addCable(string &name, string first, string second)
{
	CableParticleConnection* cable = new CableParticleConnection();

	cable->mp_first = m_particleSet[first];
	cable->mp_second = m_particleSet[second];
	float mLength = Vector3::getDistance(cable->mp_second->getPosition(),
											cable->mp_first->getPosition());
	cable->setMaxLength(mLength);
	cable->setRestitution(0.5f);

	// Add contact generator to registry
	//m_particleContactRegistry[name] = cable;
	m_particleContactRegistry.add(name, cable);
	return name;
}

string PhysicsManager::addSpring(string &name, string particle, string anchor)
{
	// One generator for each side...
	Particle* partPart = m_particleSet[particle];
	Particle* anchorPart = m_particleSet[anchor];

	SpringForceGenerator* spring = new SpringForceGenerator(anchorPart); //first is anchored by second

	float restLength = Physics::Vector3::getDistance(partPart->getPosition(), anchorPart->getPosition());
	spring->setRestLength(restLength);

	//m_particleForceRegistry[name] = spring;
	m_particleForceRegistry.add(name, spring);

	ForceRegistration registration;
	registration.generator = spring;
	registration.particle = partPart;
	m_forceRegistrations.add(registration);
	return name;
}

string PhysicsManager::addCollisionSphere(string &name, string &bodyName)
{
	return addCollisionSphere(name, bodyName, 0.5f);
}

string PhysicsManager::addCollisionSphere(string &name, string &bodyName, float radius)
{
	if (hasRigidBody(bodyName) && !hasSphereCollider(name))
	{
		RigidBody* body = getRigidBody(bodyName);
		if (body != nullptr)
		{
			CollisionSphere* sphere = new CollisionSphere();
			sphere->body = body;
			sphere->radius = radius;

			m_colliders.add(name, sphere);
			return name;
		}
		else return "";
	}
	else return "";
}
