#pragma once
#include "ForceGenerator.h"

class GravityGenerator : public ForceGenerator
{
public:
	GravityGenerator() : ForceGenerator(Vector3D(0, 0, 0)) {}
	virtual void applyForce(Particle* p, const double dt) override;
};
