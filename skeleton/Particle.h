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
	Particle(Vector3D Pos, Vector3D Vel, Vector3D Accel, float Damping, Integrator integratorType);
	~Particle();

	void integrate(double t);

private:
	Vector3D vel;
	Vector3D accel;
	physx::PxTransform pose;
	float damping;

	RenderItem* renderItem;
	Integrator currIntegrator;

	// Metodo para cada integrador
	void eulerIntegrate(double t);
	void semiEulerIntegrate(double t);
	void verletIntegrate(double t);
};

