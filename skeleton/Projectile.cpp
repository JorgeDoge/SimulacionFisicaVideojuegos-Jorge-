#include "Projectile.h"

Projectile::Projectile(ParticleData& data, const float Damping, const Integrator integratorType)
	: Particle(data, Damping, integratorType)
{
}

// Se usará más adelante(?)
void Projectile::integrate(const double t)
{


	Particle::integrate(t);
}