#pragma once

#include <vector>
#include "RenderUtils.hpp"
#include "Vector3D.h"
#include "ForceGenerator.h"

enum Integrator
{
	Euler,
	SemiEuler,
	Verlet
};


struct ParticleData
{
	float mass;
	Vector3D pos;
	Vector3D dir;
	float speed;
	Vector3D accel;
	float lifetime;

	ParticleData(const float newMass, const Vector3D newPos, const Vector3D newDir, const float newSpeed, const Vector3D newAccel, float newLifetime = 2.0f)
		: mass(newMass), pos(newPos), dir(newDir), speed(newSpeed), accel(newAccel), lifetime(newLifetime)
	{
	}
};

class Particle
{
public:
	Particle(ParticleData& data, float Damping = 0.98f, Integrator integratorType = Integrator::SemiEuler);
	~Particle();

	virtual void integrate(const double dt);

	void shortenLifespan(const double dt) { lifetime -= dt; }
	bool hasExpired() const { return lifetime <= 0.0f; }
	Vector3D getPos() const { return pos.p; }
	void addForce(Vector3D addedForce) { accumForce += addedForce; }

private:
	float mass;
	physx::PxTransform pos;
	physx::PxTransform lastPos;
	Vector3D vel;
	Vector3D accel;
	Vector3D accumForce;
	float lifetime;
	float damping;

	std::vector<ForceGenerator*> forces;
	RenderItem* renderItem;
	Integrator currIntegrator;

	// Metodo para cada integrador
	void eulerIntegrate(const double dt);
	void semiEulerIntegrate(const double dt);
	void verletIntegrate(const double dt);
};

