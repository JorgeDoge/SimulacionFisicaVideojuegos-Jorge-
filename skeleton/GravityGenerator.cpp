#include "GravityGenerator.h"

void GravityGenerator::applyForce(Particle* p, const double dt)
{
	p->addForce(force);
}