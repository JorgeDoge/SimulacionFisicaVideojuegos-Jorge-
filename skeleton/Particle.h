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
	float friction;
	float drag;
	float lifetime;

	ParticleData(const float newMass, const Vector3D newPos, const Vector3D newDir, const float newSpeed, const Vector3D newAccel, 
		const float newFriction = 1.0f, const float newDrag = 1.0f, float newLifetime = 15.0f)
		: mass(newMass), pos(newPos), dir(newDir), speed(newSpeed), accel(newAccel), friction(newFriction), drag(newDrag), lifetime(newLifetime)
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
	float getMass() const { return mass; }
	Vector3D getVel() const { return vel; }

	void addForce(Vector3D addedForce) { accumForce += addedForce; }
	void clearForce() { accumForce = Vector3D(0, 0, 0); }

	// Propiedades aerodinámicas
	float getFriction() const { return frictionCoeff; }
	float getDrag() const { return dragCoeff; }

private:
	float mass;
	physx::PxTransform pos;
	physx::PxTransform lastPos;
	Vector3D vel;
	Vector3D accel;
	Vector3D accumForce;
	float frictionCoeff; // Coeficiente de fricción 
	float dragCoeff; // Coeficiente aerodinámico (0.5 para esfera)
	float lifetime;
	float damping;

	RenderItem* renderItem;
	Integrator currIntegrator;

	// Metodo para cada integrador
	void eulerIntegrate(const double dt);
	void semiEulerIntegrate(const double dt);
	void verletIntegrate(const double dt);
};

