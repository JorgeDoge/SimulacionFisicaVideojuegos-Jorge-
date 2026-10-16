#pragma once
#include "Particle.h"

class Projectile : public Particle
{
public:
	Projectile(const float Mass, const Vector3D Pos, const Vector3D Vel, const Vector3D Accel, 
		const float newLifespan = 2.0f, const float Damping = 0.98f, Integrator integratorType = Integrator::SemiEuler);

	virtual void integrate(const double dt) override;
};

