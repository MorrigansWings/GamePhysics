#ifndef _PARTICLE_H_
#define _PARTICLE_H_

#pragma once 

#include "../Vectors.h"


class Particle
{
public:
	Particle()
		: position(Vector3(0.0f))
		, velocity(Vector3(0.0f))
		, acceleration(Vector3(0.0f))
		, damping(DEFAULT_DAMPING)
		, mass(DEFAULT_MASS)
		, inverseMass(1.0f/mass)
	{}
	Particle(Vector3 pos, Vector3 vel, Vector3 acc, float damp, float ma)
		: position(pos)
		, velocity(vel)
		, acceleration(acc)
		, damping(damp)
		, mass(ma)
		, inverseMass(1.0f/mass)
	{}

	~Particle(){};


	void addForce(Vector3 force);
	
	// GETTERS
	inline Vector3 getPosition() { return position; }
	inline Vector3 getVelocity() { return velocity; }
	inline Vector3 getAcceleration() { return acceleration; }
	inline float getDamping() { return damping; }
	inline float getMass(){ return mass; }
	inline float getInverseMass() { return inverseMass; }

	// SETTERS
	inline void setPositionX(float newVal){ position.x = newVal; }
	inline void setPositionY(float newVal){ position.y = newVal; }
	inline void setPositionZ(float newVal){ position.z = newVal; }
	inline void setPosition(Vector3 newVal){ position = newVal; }
	inline void setVelocityX(float newVal){ velocity.x = newVal; }
	inline void setVelocityY(float newVal){ velocity.y = newVal; }
	inline void setVelocityZ(float newVal){ velocity.z = newVal; }
	inline void setVelocity(Vector3 newVal){ velocity = newVal; }
	inline void setAccelerationX(float newVal){ acceleration.x = newVal; }
	inline void setAccelerationY(float newVal){ acceleration.y = newVal; }
	inline void setAccelerationZ(float newVal){ acceleration.z = newVal; }
	inline void setAcceleration(Vector3 newVal){ acceleration = newVal; }
	inline void setDamping(float newVal){ damping = newVal; }
	inline void setMass(float newVal)
	{ 
		mass = newVal; 
		inverseMass = 1.0f / mass; 
	}

private:
	const static float DEFAULT_DAMPING;
	const static float DEFAULT_MASS;

	void updatePosition();


	Vector3 position,
			velocity,
			acceleration;

	float	damping,
			mass,
			inverseMass;

};
#endif //_PARTICLE_H_