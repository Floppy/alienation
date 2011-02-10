#include "3D/Particle.h"

CParticle::CParticle(C3DObject* pGeometry) :
   m_vecPosition(0,0,0),
   m_vecOldPosition(0,0,0),
   m_vecAcceleration(0,0,0),
   m_fAge(0),
   m_fSize(0),
   m_fTimeToLive(0),
   m_fDistance(0),
   m_fSpeed(0),
   m_pGeometry(pGeometry)
{}

