#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Vector3D newPos, const ParticleData& data, const float newStdDeviation, const float newGravity)
    : pos(newPos), stdDeviation(newStdDeviation), gravity(newGravity), numParticles(0)
{
    pos_dist = normal_distribution<float>(0.0f, 0.1f);
    dir_dist = normal_distribution<float>(0.0f, 0.05f);
    speed_dist = normal_distribution<float>(data.speed, 1.0f);
    lifetime_dist = normal_distribution<float>(data.lifetime, 1.0f);
}

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
    ++numParticles;
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
                --numParticles;
            }

            else ++it;
        }

        else ++it;
    }

    if(numParticles < MAX_PARTICLES) spawnParticle();
}