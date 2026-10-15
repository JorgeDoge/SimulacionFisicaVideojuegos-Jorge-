#include "ParticleSystem.h"

ParticleSystem::~ParticleSystem()
{
    for (Particle* particle : m_particles)
        if (particle != nullptr) {
            delete particle; // Destructor del sistema
            particle = nullptr;
        }
}

void ParticleSystem::spawnParticle()
{
    random_device rd{};
    mt19937 gen{rd()};

    std::normal_distribution<double> normal{ 20.0f, stdDeviation };

    float randomFloat = normal(gen);

    m_particles.push_back(new Particle(0.0f, pos, Vector3D(0.0f, 0.0f, abs(randomFloat)), Vector3D(0.0f, gravity, 0.0f)));
}

void ParticleSystem::update(double dt)
{
    for (auto it = m_particles.begin(); it != m_particles.end(); )
    {
        Particle* particle = *it;
        if (particle != nullptr) {
            particle->integrate(dt);
            particle->shortenLifespan(dt);

            if (particle->hasExpired())
            {
                delete particle;
                it = m_particles.erase(it);  
            }

            else ++it;
        }

        else ++it;
    }

    spawnParticle();
}