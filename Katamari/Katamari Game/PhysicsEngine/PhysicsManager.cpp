#include "PhysicsManager.h"

#include <iostream>

#include "ForceGenerators/ParticleForceGenerator.h"
#include "ForceGenerators/GravityForceGenerator.h"
#include "Collision/ParticleContact.h"
#include "Collision/ParticleContactGenerator.h"
#include "Collision/GroundContactGenerator.h"


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
	//for (unsigned int i = 0; i < m_forceRegistrations.size(); ++i)
	//{
	//	ForceRegistration reg = m_forceRegistrations[i];
	//	reg.generator->updateForce(reg.particle, duration);
	//}

	// Integrate particle positions
	integrateParticles(duration);
	//for (auto iter = m_particleSet.itBegin(); iter != m_particleSet.itEnd(); ++iter)
	//	iter->second->integrate(duration);

	//TESTING
	//std::cout << "PARTICLES! =================================" << std::endl;
	//for (auto iter = m_particleSet.itBegin(); iter != m_particleSet.itEnd(); ++iter)
	//	std::cout << "Particle Position: " << iter->second->getPosition().ToString() << std::endl;

	// Compute set of all particles in contact
	generateCollisions();

	// Resolve velocities for all particles in contact
	resolveCollisions(duration);
}


void PhysicsManager::updateForces(float duration)
{
	Registry::iterator it = m_forceRegistrations.begin();
	for (; it != m_forceRegistrations.end(); ++it)
	{
		it->generator->updateForce(it->particle, duration);
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
		iter->second->AddContact(s_Instance);
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
/*
Particle* PhysicsManager::getParticle(string name)
{
	std::cout << "PHYSICSMANAGER::getParticle(): call to hasParticle(" << name << ") returns " << hasParticle(name) << std::endl;
	if (hasParticle(name))
		return m_particleSet[name];
	else return nullptr;
}

Physics::Vector3 PhysicsManager::getParticlePosition(string &name)
{
	std::cout << "PHYSICSMANAGER::getParticlePosition(): Looking for particle named " << name << "..." << std::endl;

	if (hasParticle(name))
	{
		Physics::Vector3 position = getParticle(name)->getPosition();
		std::cout << "PHYSICSMANAGER::getParticlePosition(): Found particle named " << name << "! Position: " << position.ToString() << std::endl;
		return position;
	}
	else return Vector3(0.0f);
}*/

bool PhysicsManager::applyGravity(string &name)
{
	if (m_particleSet.containsKey(name) && m_particleForceRegistry.containsKey("gravity"))
	{
		ForceRegistration newForce;
		newForce.generator = m_particleForceRegistry["gravity"];
		newForce.particle = m_particleSet[name];
		m_forceRegistrations.push_back(newForce);
		return true;
	}
	return false;
}