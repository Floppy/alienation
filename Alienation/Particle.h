/*
 *  Particle
 *
 *  Used to store particle specific data in
 *
 *  Created by Robert Schaap <robert@vulcanus.its.tudelft.nl>
 *  http://vulcanus.its.tudelft.nl/robert
 */

#ifndef _Particle_h
#define _Particle_h

#include "config.h"

#include "Math/Vector.h"
#include "Physics/Physics1.h"

//Should actually be called tParticle and be a struct rather than a class.
//Will do this soon. Handles all particle data. Used by the abstract
//CParticleengine class and its children
class CParticle
{

public:
	CVector3 m_vecPosition;
	CVector3 m_vecOldPosition;
	//CVector3 m_vecVelocity;
	CVector3 m_vecAcceleration;
	float m_fr, m_fg, m_fb, m_fa;
	float m_fAge;
	float m_fSize;
	float m_fTimeToLive;
	float m_fDistance;
	//bool m_bAlive;
	float m_fSpeed;

};

#endif

