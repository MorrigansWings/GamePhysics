#include "Vectors.h"


class Particle
{
public:
	Particle()
		: position(Vector3(0.0f))
		, velocity(Vector3(0.0f))
		, acceleration(Vector3(0.0f))
		, damping(0.0f)
		, inverseMass(0.0f)
	{}



private:
	const static float DEFAULT_DAMPING;
	const static float DEFAULT_INVERSE_MASS;

	void updatePosition();


	Vector3 position,
			velocity,
			acceleration;

	float	damping,
			inverseMass;

};