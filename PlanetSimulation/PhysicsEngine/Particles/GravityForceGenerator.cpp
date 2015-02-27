#include "GravityForceGenerator.h"

float GravityForceGenerator::GRAVITATIONAL_CONSTANT = (float)(6.673 * pow(10, -11));
float GravityForceGenerator::GAUSSIAN_CONSTANT = 0.01720209895f;

GravityForceGenerator::GravityForceGenerator()
{

}

GravityForceGenerator::~GravityForceGenerator()
{

}

void GravityForceGenerator::updateForce(Particle* particle, float duration)
{
	particle->addForce(gravity * particle->getMass());
}