#include "Whirlwind.h"
#include "Particle.h"

void Whirlwind::applyForce(Particle* p, const double dt)
{
	const Vector3D rParticle = p->getPos() - originPos;
	const float distance = sqrt(pow(rParticle.x, 2) + pow(rParticle.z, 2));

	// Comprobamos si la particula se encuentra en el área en la que surte efecto el torbellino
	if (distance < radius)
	{
		// K * [-(z - zc), 0, (x - xc)]
		const Vector3D currentWindVel = Vector3D(-(p->getPos().z - originPos.z), 
			0.0f, 
			(p->getPos().x - originPos.x)) * windForce;

		// Aplicar la fuerza usando la velocidad calculada
		const Vector3D speedDiff = currentWindVel - p->getVel();
		const float quadraticCoeff = p->getDrag() * density;
		force = speedDiff * p->getFriction() + ((speedDiff * speedDiff.magnitude()) * 0);
		p->addForce(force);
	}
}