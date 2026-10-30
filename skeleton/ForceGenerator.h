#pragma once
#include "Vector3D.h"

class Particle; 

class ForceGenerator
{
public:
	ForceGenerator(const Vector3D& genForce) : force(genForce) {}
	virtual void applyForce(Particle* p, const double dt);

protected:
	Vector3D force;
};
		
class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator() : ForceGenerator(Vector3D(0, 0, 0)) {}
	virtual void applyForce(Particle* p, const double dt) override;
};

class WindForceGenerator : public ForceGenerator
{
public:
	WindForceGenerator(const Vector3D& vel) : ForceGenerator(Vector3D(0, 0, 0)), windVel(vel) {}
	virtual void applyForce(Particle* p, const double dt);

protected:
	Vector3D windVel;
};

