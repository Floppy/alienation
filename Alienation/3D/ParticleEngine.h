/*
 *  Particle Engine (abstract)
 *
 *  Standard particle engine, used to create specific
 *  particle engines with (not supposed to be
 *  instantiated as an actual particle system)
 *
 *  Created by Robert Schaap <robert@vulcanus.its.tudelft.nl>
 *  http://vulcanus.its.tudelft.nl/robert
 */

#ifndef _Particle_Engine_h
#define _Particle_Engine_h

#include "config.h"

#include "Physics/Physics1.h"
#include "Particle.h"
#include "Math/Vector.h"

//Nicked this and amended it a LOT. It was really desigh=ned for static particle displays.
//It is a totally abstract class (note the pure virtuals). In later releases I may make it
//non abstract and put a lot of the code here for the children to inherit 
class CParticleEngine
{

protected:
	CVector3 m_vecShape[4];                             // For particle systems that use specific shapes
	int m_iParticlesCreated;                            // Number of particles used in particle list
	int m_iNumParticles;
public:
	CVector3 m_vecOrigin;

    // Constructors/destructor
	CParticleEngine(int iNumParticles, CVector3 vecOrigin);
	CParticleEngine(void);
	virtual ~CParticleEngine(void);
	CParticle * m_poParticles;                          // List of particles

	


	virtual void reset(void);                           // Resets entire particle system
	virtual void resetParticle(int i) = 0;              // Resets specific particle (with index i)
	virtual void update(float fDT) = 0;		    // Updates particle system
	virtual void render(void) = 0;                      // Render particles to the screen

};

#endif
