// Brake.h: interface for the CBrake class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BRAKE_H__56947D38_1F83_4127_AD3D_D52EA855FBEB__INCLUDED_)
#define AFX_BRAKE_H__56947D38_1F83_4127_AD3D_D52EA855FBEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <time.h>
#include "ParticleEngine.h"
#include "texture.h"
#include "matrix.h"
//Draws (badly) a brake trail at the front of the ship. Was done in 10 minutes flat
//and need far more time. For this reason didnt make the demo. Works similary to the 
//trail class, best off looking at the comments there first
class CBrake : public CParticleEngine  
{
public:
	CBrake(int _numParticles, CVector3 _vecOrigin);
	virtual ~CBrake();
	void init();
	void resetParticle(int i);										// Resets specific particle (with index i)
	void update(float fDT, CVector3 vecPos, CVector3 vecHead, CVector3 vecStart, bool bKeyDown);
	void update(float fDT);                        // Updates particle system
	void render(void);                                    // Render particles to the screen
	void createParticle(int i, CVector3 vecHead, CVector3 vecPos);
	void reset();
private:
	CTexture *m_poTexture;
};

#endif // !defined(AFX_BRAKE_H__56947D38_1F83_4127_AD3D_D52EA855FBEB__INCLUDED_)
