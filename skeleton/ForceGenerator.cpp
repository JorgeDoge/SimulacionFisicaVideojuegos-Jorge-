#include "ForceGenerator.h"
#include "Particle.h"

void ForceGenerator::applyForce(Particle* p, const double dt)
{
	p->addForce(force);
}

void GravityGenerator::applyForce(Particle* p, const double dt)
{
	p->addForce(Vector3D(0, -9.8f, 0) * p->getMass());
}

void WindForceGenerator::applyForce(Particle* p, const double dt)
{
	// Comprobamos si la particula se encuentra en el volumen en el que surte efecto el viento
	if(p->getPos().x >= (volumePos.x - volumeOfEffect.x / 2) && p->getPos().x <= (volumePos.x + volumeOfEffect.x / 2)
		&& p->getPos().y >= (volumePos.y - volumeOfEffect.y / 2) && p->getPos().y <= (volumePos.y + volumeOfEffect.y / 2)
		&& p->getPos().z >= (volumePos.z - volumeOfEffect.z / 2) && p->getPos().z <= (volumePos.z + volumeOfEffect.z / 2))
	{
		// F = k1·(v.w - v.p) + k2·||v.w - v.p||·(v.w - v.p)
		const Vector3D speedDiff = windVel - p->getVel();
		const float quadraticCoeff = p->getDrag() * density; // Faltaria el area de incidencia del viento en la particula
		force = speedDiff * p->getFriction() + ((speedDiff * speedDiff.magnitude()) * 0);
		p->addForce(force);
	}

}