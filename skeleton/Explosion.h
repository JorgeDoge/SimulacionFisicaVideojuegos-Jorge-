#pragma once
#include "ForceGenerator.h"

class Explosion : public ForceGenerator
{
public:
	Explosion(const Vector3D& expCenter, const float expRadius, const float expIntensity = 100000.0f, 
		const float expTimeConst = 1.0f)
		: ForceGenerator(Vector3D(0, 0, 0)), center(expCenter), radius(expRadius),
		intensity(expIntensity), timeConst(expTimeConst), timeElapsed(0.0f) {}

	virtual void applyForce(Particle* p, const double dt) override;
	virtual void update(const double dt) override;
	void reset();

protected:
	Vector3D center;
	float radius;
	float intensity;
	float timeConst;
	float timeElapsed;    
};
