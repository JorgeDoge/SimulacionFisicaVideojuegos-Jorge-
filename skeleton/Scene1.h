#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include "Particle.h"
#include "Projectile.h"
#include "ParticleSystem.h"

using namespace std;

const float MAX_REAL_SPEED = 10000.0f;
const float MAX_SPEED = 100.0f;

class Scene1 : public Scene {
public:
    explicit Scene1(std::string name) : Scene(std::move(name)) {}

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
        physx::PxTransform* targetPos = new physx::PxTransform(0.0f, 20.0f, 0.0f);
        m_transforms.push_back(targetPos);
        physx::PxShape* target = CreateShape(physx::PxSphereGeometry(5.0f));
        m_renderItems.push_back(new RenderItem(target, targetPos, Vector4(0.0f, 0.0f, 1.0f, 1.0f)));

        ParticleSystem* newSystem = new ParticleSystem(targetPos->p, 2.0f);
        m_particleSystems.push_back(newSystem);
    }

    void update(double dt) override {
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

        for (ParticleSystem* system : m_particleSystems)
            if (system != nullptr) {
                system->update(dt);
            }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'f' || key == 'F') {
            ProjectileData bullet(0.008f, 300.0f, m_gravity);

			shoot(camera, bullet); // Dispara un proyectil
        }

        else if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }

        else if (key == 'q' || key == 'Q') {
            m_bulletSpeed -= 10.0f; // Reducimos velocidad de los proyectiles
        }

        else if (key == 'e' || key == 'E') {
            m_bulletSpeed += 10.0f; // Aumentamos velocidad de los proyectiles
        }
    }

    void cleanup() override {
        for (RenderItem* item : m_renderItems)
            if (item != nullptr) {
                item->release(); // Deregistra y destruye el item
                item = nullptr;
            }

        for (Particle* particle : m_particles)
            if (particle != nullptr) {
                delete particle; // Destructor de la particula
                particle = nullptr;
            }

        for (ParticleSystem* system : m_particleSystems)
            if (system != nullptr) {
                delete system; // Destructor del sistema
                system = nullptr;
            }
    }

    void shoot(const physx::PxTransform& pos, ProjectileData data)
    {
        // Si la velocidad supera el límite, se escalan los datos
        if (data.speed > MAX_SPEED) scale(data);

        // Dirección perpendicular al puerto de vista de la cámara
		Vector3D direction = Vector3D(pos.q.rotate(physx::PxVec3(0, 0, -1))).normalize(); 

        // Creamos el proyectil
        Projectile* newProjectile = new Projectile(data.mass, pos.p, direction * data.speed, Vector3D(0.0f, data.accel, 0.0f));
        m_particles.push_back(newProjectile);
    }

    void scale(ProjectileData& data)
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
};