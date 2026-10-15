#pragma once

#include "RenderUtils.hpp"
#include "Vector3D.h"

enum Integrator
{
	Euler,
	SemiEuler,
	Verlet
};

class Particle
{
public:
	Particle(const float Mass, Vector3D Pos, Vector3D Vel, Vector3D Accel = Vector3D(0.0f, 0.0f, 0.0f), 
		float Damping = 0.98f, float newLifespan = 2.0f, Integrator integratorType = Integrator::SemiEuler);
	~Particle();

	virtual void integrate(const double dt);
	void shortenLifespan(const double dt) { lifespan -= dt; }
	bool hasExpired() const { return lifespan <= 0.0f; }

private:
	float mass;
	Vector3D vel;
	Vector3D accel;
	physx::PxTransform pos;
	physx::PxTransform lastPos;
	float damping;
	float lifespan;

	RenderItem* renderItem;
	Integrator currIntegrator;

	// Metodo para cada integrador
	void eulerIntegrate(const double dt);
	void semiEulerIntegrate(const double dt);
	void verletIntegrate(const double dt);
};

