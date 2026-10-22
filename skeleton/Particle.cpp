#include "Particle.h"

Particle::Particle(ParticleData& data,  const float Damping, const Integrator integratorType)
	: mass(data.mass), pos(data.pos), lastPos(physx::PxTransform(0, 0, 0)), vel(data.dir * data.speed), accel(data.accel),
	lifetime(data.lifetime), damping(Damping), currIntegrator(integratorType)
{
	physx::PxShape* sphere = CreateShape(physx::PxSphereGeometry(1.0f));
	renderItem = new RenderItem(sphere, &pos, Vector4(1.0f, 1.0f, 1.0f, 1.0f)); 
}

Particle::~Particle()
{
	renderItem->release();
}

void Particle::integrate(const double dt)
{
	// Integrador de Euler
	if (currIntegrator == Integrator::Euler) eulerIntegrate(dt);

	// Integrador de Euler semi-implicito
	else if (currIntegrator == Integrator::SemiEuler) semiEulerIntegrate(dt);

	// Integrador de Verlet (por hacer)
	else if (currIntegrator == Integrator::Verlet)
	{
		if (lastPos.p != pos.p) verletIntegrate(dt);

		else
		{
			lastPos = pos;
			semiEulerIntegrate(dt);
		}
	}
}

void Particle::eulerIntegrate(const double dt)
{
	pos.p += vel * dt;
	vel += accel * dt;
	vel = vel * pow(damping, dt);
}

void Particle::semiEulerIntegrate(const double dt)
{
	vel += accel * dt;
	pos.p += vel * dt;
	vel = vel * pow(damping, dt);
}

void Particle::verletIntegrate(const double dt)
{
	physx::PxTransform currPos = pos;

	pos.p = 2 * pos.p - lastPos.p + physx::PxTransform(accel * pow(dt, 2)).p;
	lastPos = currPos;
}