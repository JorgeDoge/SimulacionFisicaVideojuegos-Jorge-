#pragma once

#include <vector>

using namespace std;

class Particle;
class ForceGenerator;

class ParticleForceRegistry
{
public:
	void add(Particle* particle, ForceGenerator* generator);
	void remove(Particle* particle, ForceGenerator* generator);
	void removeParticle(Particle* particle);
	void clear();
	void updateForces(double dt);

private:
	vector<pair<Particle*, ForceGenerator*>> registrations;

};
