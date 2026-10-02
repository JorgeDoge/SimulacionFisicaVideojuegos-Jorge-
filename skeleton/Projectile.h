#pragma once
#include "Particle.h"

class Projectile : public Particle
{
public:
	Projectile(float Mass, Vector3D Pos, Vector3D Vel, Vector3D Accel, float Damping, Integrator integratorType);

	virtual void integrate(double t) override;

private:
	float mass;
};

