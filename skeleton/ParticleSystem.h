#pragma once
#include <vector>
#include <random>
#include "Vector3D.h"
#include "Particle.h"

using namespace std;

class ParticleSystem
{
	ParticleSystem(const Vector3D newPos, const float newStdDeviation, const float newGravity = -10.0f)
		: pos(newPos), stdDeviation(newStdDeviation), gravity(newGravity)
	{
	}

	void spawnParticle();
	void update(double dt);

private:
	Vector3D pos;
	vector<Particle*> m_particles;
	float stdDeviation;
	float gravity;
};

