#pragma once
#include "Particle.h"

struct ProjectileData
{
	float mass;
	float speed;
	float accel;

	ProjectileData(const float newMass, const float newSpeed, const float newAccel) : mass(newMass), speed(newSpeed), accel(newAccel)
	{
	}
};

class Projectile : public Particle
{
public:
	Projectile(float Mass, Vector3D Pos, Vector3D Vel, Vector3D Accel, float Damping, Integrator integratorType);

	virtual void integrate(double t) override;

private:
	float mass;
};

