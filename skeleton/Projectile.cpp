#include "Projectile.h"

Projectile::Projectile(const float Mass, const Vector3D Pos, const Vector3D Vel, const Vector3D Accel, 
	const float newLifespan, const float Damping, const Integrator integratorType)
	: Particle(Mass, Pos, Vel, Accel, Damping, newLifespan, integratorType)
{
}

// Se usará más adelante(?)
void Projectile::integrate(const double t)
{


	Particle::integrate(t);
}