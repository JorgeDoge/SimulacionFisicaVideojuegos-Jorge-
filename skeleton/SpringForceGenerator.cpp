#include "SpringForceGenerator.h"
#include "Particle.h"

void SpringForceGenerator::applyForce(Particle* particle, double dt)
{
	Vector3D relPosVector = other->getPos() - particle->getPos();

	const float length = relPosVector.magnitude();
	const float deltaX = length - restingLength;

	Vector3D force = relPosVector * deltaX * k;

	particle->addForce(force);
}