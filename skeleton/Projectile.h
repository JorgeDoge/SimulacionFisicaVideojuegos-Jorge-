#pragma once
#include "Particle.h"

class Projectile : public Particle
{
public:
	Projectile(ParticleData& data, const float Damping = 0.98f, Integrator integratorType = Integrator::SemiEuler);

	virtual void integrate(const double dt) override;
};

