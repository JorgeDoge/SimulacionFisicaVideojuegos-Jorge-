#pragma once
#include <vector>
#include <random>
#include "Vector3D.h"
#include "Particle.h"

using namespace std;

constexpr int MAX_PARTICLES = 100;

struct DistributionData
{
	float 
};

class ParticleSystem
{
public:
	ParticleSystem(const Vector3D newPos, const ParticleData& data, const float newStdDeviation, const float newGravity = -10.0f);
	~ParticleSystem();
	void update(double dt);

private:
	Vector3D pos;
	vector<Particle*> m_particles;
	float stdDeviation;
	float gravity;
	int numParticles;
	default_random_engine generator;
	normal_distribution<float> pos_dist;
	normal_distribution<float> speed_dist;
	normal_distribution<float> dir_dist;
	normal_distribution<float> lifetime_dist;

	void spawnParticle();
};

