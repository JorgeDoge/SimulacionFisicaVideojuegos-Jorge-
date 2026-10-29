#include "ForceGenerator.h"
#include "Particle.h"

void ForceGenerator::applyForce(Particle* p, const double dt)
{
	p->addForce(force);
}
