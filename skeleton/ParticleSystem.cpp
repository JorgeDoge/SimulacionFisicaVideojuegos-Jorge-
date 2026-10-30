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
    m_forceRegistry.clear();

    for (Particle* particle : m_particles)
        if (particle != nullptr) {
            delete particle; // Destructor del sistema
            particle = nullptr;
        }

    for (ForceGenerator* force : m_forces)
        if (force != nullptr) {
            delete force; // Destructor de generadores de fuerzas
            force = nullptr;
        }
}

void ParticleSystem::update(const double dt)
{
    // Las fuerzas se acumulan una vez al comienzo del ciclo de física.
    for (Particle* particle : m_particles)
        if (particle != nullptr)
            particle->clearForce();

    m_forceRegistry.updateForces(dt);

    for (auto it = m_particles.begin(); it != m_particles.end(); )
    {
        Particle* particle = *it;
        if (particle != nullptr) {
            particle->integrate(dt);
            particle->shortenLifespan(dt);

            if (particle->hasExpired() || !checkBounds(particle->getPos()))
            {
                m_forceRegistry.removeParticle(particle);
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
    for (ForceGenerator* force : m_forces)
        m_forceRegistry.add(m_particles.back(), force);
    ++numParticles;
}

void ParticleSystem::addForce(ForceGenerator* newForce)
{
    if (newForce == nullptr) return;

    m_forces.push_back(newForce);
    for (Particle* particle : m_particles)
        m_forceRegistry.add(particle, newForce);
}

bool ParticleSystem::checkBounds(const Vector3D& particlePos) {
    float const boxLength = PARTICLE_BOUNDS / 2.0f;

    // Comprobamos si la partícula se sale del "cubo" que representa su zona
    if ((abs(particlePos.x - pos.x) > boxLength) || (abs(particlePos.y - pos.y) > boxLength) || (abs(particlePos.z - pos.z ) > boxLength)) return false;

    return true;
}