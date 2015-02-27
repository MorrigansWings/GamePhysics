#ifndef _DRAG_FORCE_GENERATOR_H_
#define _DRAG_FORCE_GENERATOR_H_

#pragma once

#include "ParticleForceGenerator.h"
#include "../Vectors.h"

class DragForceGenerator : ParticleForceGenerator
{
public:
	DragForceGenerator(){}
	DragForceGenerator(float one, float two)
		: k1(one)
		, k2(two)
	{}

	~DragForceGenerator(){};

	virtual void updateForce(Particle* particle, float duration);


private:
	float	k1,
			k2;


};
#endif //_DRAG_FORCE_GENERATOR_H_