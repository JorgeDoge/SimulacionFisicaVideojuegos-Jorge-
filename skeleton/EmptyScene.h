#pragma once

#include "Scene.h"
#include "RenderUtils.hpp"
#include <vector>
#include "Vector3D.h"

using namespace std;

class EmptyScene : public Scene {
public:
    explicit EmptyScene(std::string name) : Scene(std::move(name)) {}

    void init() override {
        // Ejemplo: Creación de una esfera usando las utilidades de render existentes
        physx::PxShape* shape = CreateShape(physx::PxSphereGeometry(2.0f));
        m_transform = physx::PxTransform(physx::PxVec3(0.0f, 10.0f, 0.0f));

        // Se registra el RenderItem exactamente como en la plantilla original
        m_renderItems.push_back(new RenderItem(shape, &m_transform, Vector4(1.0f, 1.0f, 0.0f, 1.0f)));

        Vector3D u(3.0f, 1.0f, 0.0f);
        Vector3D v(0.0f, 4.0f, 0.0f);
    }

    void update(double dt) override {
        // Lógica/Integración del alumno (por ejemplo, movimiento simple)
        //m_transform.p.y -= static_cast<float>(9.8 * dt);
    }

    void keyPress(unsigned char key, const physx::PxTransform& camera) override {
        if (key == 'r' || key == 'R') {
            m_transform.p = physx::PxVec3(0.0f, 10.0f, 0.0f); // Reset
        }
    }

    void cleanup() override {
        for(RenderItem* item : m_renderItems)
        if (item) {
            item->release(); // Deregistra y destruye el item
            item = nullptr;
        }
    }

private:
    physx::PxTransform m_transform;
    vector<RenderItem*> m_renderItems;
};