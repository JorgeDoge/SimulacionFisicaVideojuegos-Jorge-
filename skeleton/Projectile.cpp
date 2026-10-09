#include "Projectile.h"

Projectile::Projectile(const float Mass, const Vector3D Pos, const Vector3D Vel, const Vector3D Accel, 
	const float Damping, const float newLifespan, const Integrator integratorType)
	: Particle(Pos, Vel, Accel, Damping, newLifespan, integratorType), mass(Mass)
{
}

// Se usará más adelante(?)
void Projectile::integrate(const double t)
{


	Particle::integrate(t);
}