#include "RigidBodyGravityGenerator.h"

#include <iostream>

float RigidBodyGravityGenerator::EARTH_GRAVITY = 9.807f; // in Newtons!

RigidBodyGravityGenerator::RigidBodyGravityGenerator()
{
	gravity = Vector3(0.0f);
	gravity.y = -EARTH_GRAVITY;
}

RigidBodyGravityGenerator::RigidBodyGravityGenerator(float scalar)
{
	gravity = Vector3(0.0f);
	gravity.y = -EARTH_GRAVITY * scalar;
}

void RigidBodyGravityGenerator::updateForce(RigidBody* body, float duration)
{
	body->addForce(gravity * body->getMass());
	//std::cout << "GRAVITYFORCEGENERATOR:updateForce(): adding force to particle: " << (gravity * body->getMass()).ToString() << std::endl;
}