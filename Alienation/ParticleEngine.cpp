/*
 *  Particle Engine implementation
 *
 *  Created by Robert Schaap <robert@vulcanus.its.tudelft.nl>
 *  http://vulcanus.its.tudelft.nl/robert
 */

#include "particleengine.h"

// Empty constructor
CParticleEngine::CParticleEngine(void)
{
}

// Constructor
CParticleEngine::CParticleEngine(int iNumParticles, CVector3 vecOrigin)
{
    m_iNumParticles = iNumParticles;               // Set number of particles
    vecOrigin = vecOrigin;                           // Set origin of particles

    m_poParticles = new CParticle[m_iNumParticles];     // Create particle list
}

// Destructor
CParticleEngine::~CParticleEngine(void)
{
    if (m_poParticles)                              // If particle list exists...
    {
        delete[] m_poParticles;                     // Delete it
        m_poParticles = NULL;
    }
}

// Reset entire particle system
void CParticleEngine::reset(void)
{
	for (long i = 0; i < m_iNumParticles; i++)
		resetParticle(i);                       // Reset every particle
}

