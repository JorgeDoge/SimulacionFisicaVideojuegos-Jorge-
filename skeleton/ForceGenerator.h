#pragma once
#include "Vector3D.h"

class Particle;  // Forward declaration

class ForceGenerator
{
public:
	ForceGenerator(const Vector3D genForce) : force(genForce) {}
	virtual void applyForce(Particle* p, const double dt);

protected:
	Vector3D force;
};
		