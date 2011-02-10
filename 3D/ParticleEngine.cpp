/*
 *  Particle Engine implementation
 *
 *  Created by Robert Schaap <robert@vulcanus.its.tudelft.nl>
 *  http://vulcanus.its.tudelft.nl/robert
 */

#include "ParticleEngine.h"

// Empty constructor
CParticleEngine::CParticleEngine(void) :
   m_iParticlesCreated(0),
   m_iNumParticles(0),
   m_poParticles(NULL)
{
}

// Constructor
CParticleEngine::CParticleEngine(int iNumParticles, CVector3 vecOrigin) :
   m_iParticlesCreated(0),
   m_iNumParticles(0),
   m_poParticles(NULL)
{
   setup(iNumParticles,vecOrigin);
}

void CParticleEngine::setup(int iNumParticles, CVector3 vecOrigin)
{
	delete [] m_poParticles;
	m_poParticles = NULL;
    m_iNumParticles = iNumParticles;               // Set number of particles
    m_vecOrigin = vecOrigin;                           // Set origin of particles
    m_poParticles = new CParticle[m_iNumParticles];     // Create particle list
	m_iParticlesCreated = 0;
}

// Destructor
CParticleEngine::~CParticleEngine(void)
{
    delete[] m_poParticles;                     // Delete it
    m_poParticles = NULL;
}

// Reset entire particle system
void CParticleEngine::reset(void)
{
	for (long i = 0; i < m_iNumParticles; i++)
		resetParticle(i);                       // Reset every particle
}

