#include "ParticleSystem.h"

void ParticleSystem::spawnParticle()
{
    random_device rd{};
    mt19937 gen{rd()};

    std::normal_distribution<double> normal{ 0.0f, stdDeviation };

    float randomFloat = normal(gen);

    m_particles.push_back(new Particle(pos, Vector3D(0.0f, 0.0f, abs(randomFloat)), Vector3D(0.0f, gravity, 0.0f)));
}

void ParticleSystem::update(double dt)
{
    for (Particle* particle : m_particles)
        if (particle != nullptr) {
            particle->integrate(dt);
            particle->shortenLifespan(dt);

            // Falta arreglar esto
            if (particle->hasExpired())
            {
                delete particle;
                particle = nullptr;
            }
        }

    spawnParticle();
}