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

class Scene2 : public Scene {
public:
    explicit Scene2(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        //physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transform = physx::PxTransform(0.0f, 0.0f, 0.0f);
        m_bulletSpeed = 10.0f;

        // Gravedad en la tierra
        m_gravity = -9.81f;

        // "Origen de la explosión"
        physx::PxTransform* originPos = new physx::PxTransform(0.0f, 10.0f, 0.0f);
        m_transforms.push_back(originPos);
        physx::PxShape* expOrigin = CreateShape(physx::PxSphereGeometry(5.0f));
        m_renderItems.push_back(new RenderItem(expOrigin, originPos, Vector4(1.0f, 0.0f, 0.0f, 1.0f)));

        // Sistemas de partículas
        ParticleData particleData(8.0f, Vector3D(0.0f, 0.0f, 0.0f), Vector3D(0.0f, 0.0f, 0.0f), 0.0f, Vector3D(0.0f, 0, 0.0f));

        DistributionData expDist(20.0f, 1.0f, 1.0f, 1.0f);

        ParticleSystem* expSystem = new ParticleSystem(originPos->p, particleData, expDist);

        m_particleSystems.push_back(expSystem);

        m_forces.push_back(new GravityGenerator());
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

            ParticleData bulletData(0.008f, camera.p, direction, 300.0f, Vector3D(0.0f, 0.0f, 0.0f));
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

        else if (key == 'g' || key == 'G') {
            m_forces[0]->setActive(!m_forces[0]->active()); // Activamos/desactivamos gravedad de nuestros proyectiles
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
                delete system; // Destructor del sistema de partículas
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