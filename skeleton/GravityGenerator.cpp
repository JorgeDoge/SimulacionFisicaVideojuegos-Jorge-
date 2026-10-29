#include "GravityGenerator.h"
#include "Particle.h"

void GravityGenerator::applyForce(Particle* p, const double dt)
{
	force = Vector3D(0, -9.8f, 0) * p->getMass();
	p->addForce(force);
}