#include "Projectile.h"

Projectile::Projectile(float Mass, Vector3D Pos, Vector3D Vel, Vector3D Accel, float Damping, Integrator integratorType)
	: Particle(Pos, Vel, Accel, Damping, integratorType)
{
	mass = Mass;
}

void Projectile::integrate(double t)
{


	Particle::integrate(t);
}