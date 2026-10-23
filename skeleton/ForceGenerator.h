#pragma once
#include "Particle.h"

class ForceGenerator
{
public:
	ForceGenerator(const Vector3D genForce) : force(genForce) {}
	virtual void applyForce(Particle* p, const double dt) = 0;

protected:
	Vector3D force;
};
