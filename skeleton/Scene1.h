#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"
#include "Particle.h"

using namespace std;

class Scene1 : public Scene {
public:
    explicit Scene1(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        //physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f));

        Particle newParticle(Vector3D(0, 0, 0), Vector3D(2.0f, 2.0f, 0.0f));
        m_particles.push_back(newParticle);

        /*
        Particle newParticle(Vector3D(0, 0, 0), Vector3D(2.0f, 2.0f, 0.0f));
        // Crear la partícula en el heap y guardarla en el vector de punteros.
        // Se proporciona aceleración nula, un factor de damping y el tipo de integrador.
        Particle* newParticle = new Particle(Vector3D(0, 0, 0), Vector3D(2.0f, 2.0f, 0.0f), Vector3D(0, 0, 0), 0.99f, Euler);
        m_particles.push_back(newParticle);
        */
    }

    void update(double dt) override {
        for (Particle* particle : m_particles)
            if (particle) {
                particle->integrate(dt); // Destructor de la particula
                particle = nullptr;
            }
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
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

private:
    vector<physx::PxTransform> transforms;
    physx::PxTransform m_transform;
    vector<RenderItem*> m_renderItems;
    vector<Particle*> m_particles;
};