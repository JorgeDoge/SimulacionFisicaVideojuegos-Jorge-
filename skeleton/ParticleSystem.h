#pragma once
#include <vector>
#include <random>
#include "Vector3D.h"
#include "Particle.h"
#include "ParticleForceRegistry.h"

using namespace std;

constexpr int MAX_PARTICLES = 100;
constexpr float PARTICLE_BOUNDS = 500.0f;

struct DistributionData
{
	float posDev;
	float dirDev;
	float spdDev;
	float lifeDev;

	DistributionData(const float newPosDev, const float newDirDev, const float newSpdDev, const float newLifeDev)
		: posDev(newPosDev), dirDev(newDirDev),spdDev(newSpdDev), lifeDev(newSpdDev)
	{}
};

class ParticleSystem
{
public:
	ParticleSystem(const Vector3D newPos, const ParticleData& data, const DistributionData& distData = { 0.1f, 0.05f, 1.0f, 1.0f });
	~ParticleSystem();
	void update(const double dt);
	void addForce(ForceGenerator* newForce);

private:
	Vector3D pos;
	ParticleData particlesData;
	vector<Particle*> m_particles;
	vector<ForceGenerator*> m_forces;
	ParticleForceRegistry m_forceRegistry;
	int numParticles;

	default_random_engine generator;
	normal_distribution<float> pos_dist;
	normal_distribution<float> speed_dist;
	normal_distribution<float> dir_dist;
	normal_distribution<float> lifetime_dist;

	void spawnParticle();
	bool checkBounds(const Vector3D& particlePos);
};

