#include "CollisionPrimitive.h"

void CollisionPrimitive::calculateInternals()
{
	transform = body->getTransform() * offset;
}