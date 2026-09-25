#include "Particle.h"

Particle::Particle(Vector3D Pos, Vector3D Vel, Vector3D Accel = Vector3D(0.0f, 0.0f, 0.0f), float Damping = 0.98f, Integrator integratorType = Integrator::SemiEuler)
{
	pose = physx::PxTransform(Pos);
	vel = Vel;
	accel = Accel;
	damping = Damping;

	physx::PxShape* sphere = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(sphere, &pose, Vector4(1.0f, 1.0f, 1.0f, 1.0f)); 
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
		

	}
}

void Particle::eulerIntegrate(double t)
{
	pose.p.x += vel.x * t;
	pose.p.y += vel.y * t;
	pose.p.z += vel.z * t;
	vel += accel * t;
	vel = vel * pow(damping, t);
}

void Particle::semiEulerIntegrate(double t)
{
	vel += accel * t;
	pose.p.x += vel.x * t;
	pose.p.y += vel.y * t;
	pose.p.z += vel.z * t;
	vel = vel * pow(damping, t);
}