#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Accel = Vector3D(0.0f, 0.0f, 0.0f), float Damping = 0.98f, Integrator integratorType = Integrator::SemiEuler)
{
	pos = physx::PxTransform(Pos);
	lastPos = physx::PxTransform(0, 0, 0);
	vel = Vel;
	accel = Accel;
	damping = Damping;

	physx::PxShape* sphere = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(sphere, &pos, Vector4(1.0f, 1.0f, 1.0f, 1.0f)); 
	currIntegrator = integratorType;
}

Particle::~Particle()
{
	renderItem->release();
}

void Particle::integrate(double t)
{
	// Integrador de Euler
	if (currIntegrator == Integrator::Euler) eulerIntegrate(t);

	// Integrador de Euler semi-implicito
	else if (currIntegrator == Integrator::SemiEuler) semiEulerIntegrate(t);

	// Integrador de Verlet (por hacer)
	else if (currIntegrator == Integrator::Verlet)
	{
		if (!lastPos.p.isZero()) verletIntegrate(t);

		else
		{
			lastPos = pos;
			semiEulerIntegrate(t);
		}
	}
}

void Particle::eulerIntegrate(double t)
{
	pos.p += vel * t;
	vel += accel * t;
	vel = vel * pow(damping, t);
}

void Particle::semiEulerIntegrate(double t)
{
	vel += accel * t;
	pos.p += vel * t;
	vel = vel * pow(damping, t);
}

void Particle::verletIntegrate(double t)
{
	physx::PxTransform currPos = pos;

	pos.p = 2 * pos.p - lastPos.p + physx::PxTransform(accel * pow(t, 2)).p;
	lastPos = currPos;
}