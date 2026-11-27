#pragma once
#include "ForceGenerator.h"

class SpringForceGenerator : public ForceGenerator
{
public:
	SpringForceGenerator(double newK, double newRestingLength, Particle* newOther) 
		: ForceGenerator(Vector3D(0, 0, 0)), k(newK), restingLength(newRestingLength), other(newOther)
	{}

	virtual void applyForce(Particle* particle, double dt) override;

	inline void setK(double newK) { k = newK; }

protected:
	double k;
	double restingLength;
	Particle* other;
};