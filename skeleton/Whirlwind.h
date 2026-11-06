#pragma once
#include "ForceGenerator.h"

class Whirlwind : public WindForceGenerator
{
public:
	Whirlwind(const Vector3D& pos, const float r, const float force, const float p = 1.225f)
		: WindForceGenerator(pos, { 0, 0, 0 }, { 0, 0, 0 }, p), radius(r), windForce(force) {}
	virtual void applyForce(Particle* p, const double dt);

protected:
	float radius;
	float windForce;
};
