#include "ForceGenerator.h"
#include "Particle.h"

void ForceGenerator::applyForce(Particle* p, const double dt)
{
	p->addForce(force);
}

void GravityGenerator::applyForce(Particle* p, const double dt)
{
	p->addForce(Vector3D(0, -9.8f, 0) * p->getMass());
}

void WindForceGenerator::applyForce(Particle* p, const double dt)
{
	const Vector3D speedDiff = windVel - p->getVel();
	force = speedDiff * p->getFriction() + (speedDiff * speedDiff.magnitude()) * 0;
	p->addForce(force);
}