#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include "Particle.h"
#include "Projectile.h"

using namespace std;

class Scene1 : public Scene {
public:
    explicit Scene1(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        //physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f));
		m_bulletSpeed = 10.0f;
        
        // Gravedad en la tierra
        m_gravity = Vector3D(0, -9.8f, 0);

        physx::PxShape* plane = CreateShape(physx::PxPlaneGeometry());
        renderItem = new RenderItem(plane, &pos, Vector4(1.0f, 1.0f, 1.0f, 1.0f));

    }

    void update(double dt) override {
        for (Particle* particle : m_particles)
            if (particle) {
                particle->integrate(dt);
            }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'f' || key == 'F') {
			shoot(camera); // Dispara un proyectil
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
            if (item) {
                item->release(); // Deregistra y destruye el item
                item = nullptr;
            }

        for (Particle* particle : m_particles)
            if (particle) {
                delete particle; // Destructor de la particula
                particle = nullptr;
            }
    }

    void shoot(const physx::PxTransform& pos)
    {
		Vector3D direction = Vector3D(pos.q.rotate(physx::PxVec3(0, 0, -1))).normalize(); 

        Projectile* newProjectile = new Projectile(5.0f, pos.p, direction * m_bulletSpeed, m_gravity, 0.99f, SemiEuler);
        m_particles.push_back(newProjectile);
    }

    void scale()
    {
        
    }

private:
    vector<physx::PxTransform> transforms;
    float m_bulletSpeed;
    Vector3D m_gravity;
    physx::PxTransform m_transform;
    vector<RenderItem*> m_renderItems;
    vector<Particle*> m_particles;
};