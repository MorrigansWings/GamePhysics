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

PhysicsManager* PhysicsManager::s_Instance = nullptr;

PhysicsManager::PhysicsManager()
{
	s_Instance = this;

	// Set up force generators
	GravityForceGenerator* gravity = new GravityForceGenerator(2.0f); // scale gravity by 2
	m_particleForceRegistry.add("gravity", gravity);
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

	// create ground collision generator
	GroundContactGenerator* ground = new GroundContactGenerator();
	ground->setGroundHeight(m_groundHeight);
	m_particleContactRegistry.add("ground", ground);
}

void PhysicsManager::update(float duration)
{
	// Clear force accumulators
	for (auto iter = m_particleSet.itBegin(); iter != m_particleSet.itEnd(); ++iter)
		iter->second->clearAccumulation();

	// Generate forces via generators
	updateForces(duration);

	// Integrate particle positions
	integrateParticles(duration);

	// Compute set of all particles in contact
	generateCollisions();

	// Resolve velocities for all particles in contact
	resolveCollisions(duration);
}

void PhysicsManager::updateForces(float duration)
{
	//for (auto it = m_forceRegistrations.itBegin(); it != m_forceRegistrations.itEnd(); ++it)
	for (unsigned int i = 0; i < m_forceRegistrations.getSize(); ++i)
	{
		std::cout << "PHYSICSMANAGER:updateForces: Attempting to update generator " << i << std::endl; 
		ParticleForceGenerator* generator = m_forceRegistrations[i].generator;
		Particle* particle = m_forceRegistrations[i].particle;

		generator->updateForce(particle, duration);
	}
}

void PhysicsManager::integrateParticles(float duration)
{
	for (auto iter = m_particleSet.itBegin(); iter != m_particleSet.itEnd(); ++iter)
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

void PhysicsManager::resolveCollisions(float duration)
{
	for (unsigned int i = 0; i < m_contacts.getSize(); ++i)
	{
		m_contacts[i]->resolve(duration);
	}

	// clear contacts after resolution...?
	for (unsigned int i = 0; i < m_contacts.getSize(); ++i)
	{
		delete m_contacts[i];
	}
	m_contacts.clear();
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
	rod->m_maxLength = Vector3::getDistance(rod->mp_first->getPosition(),
										rod->mp_second->getPosition());

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
	cable->m_maxLength = Vector3::getDistance(cable->mp_second->getPosition(),
											cable->mp_first->getPosition());
	cable->m_restitution = 0.5f;

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

	float restLength = Physics::Vector3::getDistance(partPart->getPosition(), anchorPart->getPosition());
	SpringForceGenerator* spring = new SpringForceGenerator(anchorPart); //first is anchored by second
	spring->setRestLength(restLength);
	//spring->set

	//m_particleForceRegistry[name] = spring;
	m_particleForceRegistry.add(name, spring);

	ForceRegistration registration;
	registration.generator = spring;
	registration.particle = partPart;
	m_forceRegistrations.add(registration);
	return name;
}