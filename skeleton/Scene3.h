#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include "Particle.h"
#include "Projectile.h"
#include "ParticleSystem.h"
#include "ParticleForceRegistry.h"
#include "Whirlwind.h"
#include "Explosion.h"

class Scene3 : public Scene {
public:
    explicit Scene3(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        //physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transform = physx::PxTransform(0.0f, 0.0f, 0.0f);
        m_bulletSpeed = 10.0f;

        // Gravedad en la tierra
        m_gravity = -9.81f;

        // Suelo
        physx::PxShape* floor = CreateShape(physx::PxBoxGeometry(50.0f, 0.1f, 50.0f));
        m_renderItems.push_back(new RenderItem(floor, &m_transform, Vector4(1.0f, 1.0f, 1.0f, 1.0f)));

        // "Diana"
        physx::PxTransform* originPos = new physx::PxTransform(0.0f, 100.0f, 0.0f);
        m_transforms.push_back(originPos);
        physx::PxShape* target = CreateShape(physx::PxSphereGeometry(5.0f));
        m_renderItems.push_back(new RenderItem(target, originPos, Vector4(0.0f, 1.0f, 0.0f, 1.0f)));

        // Sistemas de partículas
        ParticleData waterData(0.1f, Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 1.0f, 0.0f), 40.0f, Vector3D(0.0f, 0, 0.0f));

        DistributionData waterDist(0.001f, 0.1f, 0.001f, 0.001f);

        ParticleSystem* fountain1 = new ParticleSystem( { 40.0f, 0.0f, 0.0f }, waterData, waterDist);
        ParticleSystem* fountain2 = new ParticleSystem({ -40.0f, 0.0f, 0.0f }, waterData, waterDist);

        m_particleSystems.push_back(fountain1);
        m_particleSystems.push_back(fountain2);

        GravityGenerator* gravity = new GravityGenerator();
        fountain1->addForce(gravity);
        fountain2->addForce(gravity);
        m_forces.push_back(gravity);
    }

    void update(double dt) override {
        for (Particle* particle : m_particles)
            if (particle != nullptr) particle->clearForce();

        m_forceRegistry.updateForces(dt);

        for (auto it = m_particles.begin(); it != m_particles.end(); )
        {
            Particle* particle = *it;
            if (particle != nullptr) {
                particle->integrate(dt);
                particle->shortenLifespan(dt);

                if (particle->hasExpired())
                {
                    m_forceRegistry.removeParticle(particle);
                    delete particle;
                    it = m_particles.erase(it);
                }

                else ++it;
            }

            else ++it;
        }

        for (ParticleSystem* system : m_particleSystems)
            if (system != nullptr) {
                system->update(dt);
            }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'v' || key == 'V') {
            // Dirección perpendicular al puerto de vista de la cámara
            Vector3D direction = Vector3D(camera.q.rotate(physx::PxVec3(0, 0, -1))).normalize();

            ParticleData bulletData(0.008f, camera.p, direction, 1000.0f, Vector3D(0.0f, 0.0f, 0.0f));
            shoot(camera, bulletData); // Dispara un proyectil
        }

        else if (key == 'b' || key == 'B') {
            // Dirección perpendicular al puerto de vista de la cámara
            Vector3D direction = Vector3D(camera.q.rotate(physx::PxVec3(0, 0, -1))).normalize();

            ParticleData basketBallData(0.6f, camera.p, direction, 20.0f, Vector3D(0.0f, 0.0f, 0.0f));
            shoot(camera, basketBallData); // Dispara un proyectil
        }

        else if (key == 'r' || key == 'R') {
            for (ParticleSystem* system : m_particleSystems)
            {
                // Explosión
                Explosion* expForceGen = new Explosion(Vector3D(0.0f, 10.0f, 0.0f), 300.0f);
                system->addForce(expForceGen);
                m_forces.push_back(expForceGen);
            }
        }
    }

    void cleanup() override {
        for (RenderItem* item : m_renderItems)
            if (item != nullptr) {
                item->release(); // Deregistra y destruye el item
            }

        m_renderItems.clear();

        for (Particle* particle : m_particles)
            if (particle != nullptr) {
                m_forceRegistry.removeParticle(particle);
                delete particle; // Destructor de la particula
            }

        m_particles.clear();

        for (ForceGenerator* force : m_forces)
            if (force != nullptr) {
                delete force; // Destructor de generadores de fuerzas
            }

        m_forces.clear();

        for (ParticleSystem* system : m_particleSystems)
            if (system != nullptr) {
                delete system; // Destructor del sistema
            }

        m_particleSystems.clear();
    }

    void shoot(const physx::PxTransform& pos, ParticleData& data)
    {
        // Si la velocidad supera el límite, se escalan los datos
        if (data.speed > MAX_SPEED) scale(data);

        // Creamos el proyectil
        Projectile* newProjectile = new Projectile(data);
        m_particles.push_back(newProjectile);
        for (ForceGenerator* force : m_forces)
            m_forceRegistry.add(newProjectile, force);
    }

    void scale(ParticleData& data)
    {
        float realSpeed = data.speed;
        float simSpeed = 5 + (20 * data.speed / MAX_SPEED);

        data.speed = simSpeed;
        data.mass = data.mass * pow(realSpeed / simSpeed, 2);
        data.accel = data.accel * pow(simSpeed / realSpeed, 2);
    }

private:
    vector<physx::PxTransform*> m_transforms;
    float m_bulletSpeed;
    float m_gravity;

    physx::PxTransform m_transform;
    vector<RenderItem*> m_renderItems;
    vector<Particle*> m_particles;
    vector<ParticleSystem*> m_particleSystems;
    vector<ForceGenerator*> m_forces;
    ParticleForceRegistry m_forceRegistry;
};