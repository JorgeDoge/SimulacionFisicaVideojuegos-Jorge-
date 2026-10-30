#include "ParticleForceRegistry.h"
#include "ForceGenerator.h"
#include "Particle.h"
#include <algorithm>

void ParticleForceRegistry::add(Particle* particle, ForceGenerator* generator)
{
	if (particle != nullptr && generator != nullptr) registrations.push_back({ particle, generator });
}

void ParticleForceRegistry::remove(Particle* particle, ForceGenerator* generator)
{
	registrations.erase(std::remove_if(registrations.begin(), registrations.end(),
		[particle, generator](const pair<Particle*, ForceGenerator*>& registration)
		{
			return registration.first == particle && registration.second == generator;
		}), registrations.end());
}

void ParticleForceRegistry::removeParticle(Particle* particle)
{
	registrations.erase(std::remove_if(registrations.begin(), registrations.end(),
		[particle](const pair<Particle*, ForceGenerator*>& registration)
		{
			return registration.first == particle;
		}), registrations.end());
}

void ParticleForceRegistry::clear()
{
	registrations.clear();
}

void ParticleForceRegistry::updateForces(const double dt)
{
	for (const pair<Particle*, ForceGenerator*>& registration : registrations)
		registration.second->applyForce(registration.first, dt);
}
