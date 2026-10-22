#include "ParticleSystem.h"

ParticleSystem::ParticleSystem(const Vector3D newPos, const ParticleData& data, const DistributionData& distData)
    : pos(newPos), particlesData(data), numParticles(0)
{
    pos_dist = normal_distribution<float>(0.0f, distData.posDev);
    dir_dist = normal_distribution<float>(0.0f, distData.dirDev);
    speed_dist = normal_distribution<float>(0.0f, distData.spdDev);
    lifetime_dist = normal_distribution<float>(particlesData.lifetime, distData.lifeDev);
}

ParticleSystem::~ParticleSystem()
{
    for (Particle* particle : m_particles)
        if (particle != nullptr) {
            delete particle; // Destructor del sistema
            particle = nullptr;
        }
}

void ParticleSystem::update(double dt)
{
    for (auto it = m_particles.begin(); it != m_particles.end(); )
    {
        Particle* particle = *it;
        if (particle != nullptr) {
            particle->integrate(dt);
            particle->shortenLifespan(dt);

            if (particle->hasExpired() || !checkBounds(particle->getPos()))
            {
                delete particle;
                it = m_particles.erase(it);
                --numParticles;
            }

            else ++it;
        }

        else ++it;
    }

    if (numParticles < MAX_PARTICLES) spawnParticle();
}

void ParticleSystem::spawnParticle()
{
    Vector3D const particlePos(pos.x + pos_dist(generator), pos.y + pos_dist(generator), pos.z + pos_dist(generator));
    Vector3D const particleDir = Vector3D(particlesData.dir.x + dir_dist(generator), particlesData.dir.y + dir_dist(generator), particlesData.dir.z + dir_dist(generator)).normalize();
    float const particleSpeed = particlesData.speed + speed_dist(generator);
    float const particleLifetime = particlesData.lifetime + lifetime_dist(generator);

    ParticleData newParticleData(particlesData.mass, particlePos, particleDir, particleSpeed, particlesData.accel, particleLifetime);
    m_particles.push_back(new Particle(newParticleData));
    ++numParticles;
}

bool ParticleSystem::checkBounds(const Vector3D& particlePos) {
    float const boxLength = PARTICLE_BOUNDS / 2.0f;

    // Comprobamos si la partícula se sale del "cubo" que representa su zona
    if ((abs(particlePos.x - pos.x) > boxLength) || (abs(particlePos.y - pos.y) > boxLength) || (abs(particlePos.z - pos.z ) > boxLength)) return false;

    return true;
}