#pragma once
#include "Particle.h"

struct ProjectileData
{
	float mass;
	float speed;
	float accel;

	ProjectileData(const float newMass, const float newSpeed, const float newAccel) 
		: mass(newMass), speed(newSpeed), accel(newAccel)
	{
	}
};

class Projectile : public Particle
{
public:
	Projectile(const float Mass, const Vector3D Pos, const Vector3D Vel, const Vector3D Accel, 
		const float Damping, const float newLifespan = 10.0f, Integrator integratorType = Integrator::SemiEuler);

	virtual void integrate(const double dt) override;

private:
	float mass;
};

