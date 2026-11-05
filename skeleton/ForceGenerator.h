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
	WindForceGenerator(const Vector3D& pos, const Vector3D& volume, const Vector3D& vel, const float p = 1.225f)
		: ForceGenerator(Vector3D(0, 0, 0)), originPos(pos), volumeOfEffect(volume), windVel(vel), density(p) {}
	virtual void applyForce(Particle* p, const double dt);

protected:
	Vector3D originPos;
	Vector3D volumeOfEffect;
	Vector3D windVel;
	float density;
};
