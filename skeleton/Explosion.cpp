#include "Explosion.h"
#include "Particle.h"
#include <cmath>

void Explosion::applyForce(Particle* p, const double dt)
{
	// Si la explosión no está activa, no aplicar fuerza
	if (!isActive) return;

	const Vector3D rParticle = p->getPos() - center;
	const float distance = rParticle.magnitude();

	// Comprobar si la partícula está dentro del radio de la explosión
	if (distance < radius && distance > 0.001f)
	{
		// F = (K / r²) * [x-xc, y-yc, z-zc] * e^(-t/τ)
		// K/r²
		float distanceFactor = intensity / (distance * distance);

		// e^(-t/τ)
		float decayFactor = exp(-timeElapsed / timeConst);

		force = rParticle * (distanceFactor * decayFactor);
		p->addForce(force);
	}
}

void Explosion::update(const double dt)
{
	if (isActive) {
		timeElapsed += dt;

		if (timeElapsed > 4.0f * timeConst) isActive = false;
	}
}

void Explosion::reset()
{
	timeElapsed = 0.0f;
	isActive = true;
}