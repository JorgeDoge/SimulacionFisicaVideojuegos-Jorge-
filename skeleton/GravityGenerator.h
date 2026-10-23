#pragma once

#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator(const Vector3D genForce) : ForceGenerator(genForce) {}
	virtual void applyForce(Particle* p, const double dt) override;
};
