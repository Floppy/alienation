// Trail.h: interface for the CTrail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAIL_H__0572019F_F31B_441D_AFAE_4247EB700A35__INCLUDED_)
#define AFX_TRAIL_H__0572019F_F31B_441D_AFAE_4247EB700A35__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ParticleEngine.h"
#include <stdio.h>
#include <time.h>
#include "vector.h"
#include "texture.h"
#include "matrix.h"

#include <gl\gl.h>    // Header File For The OpenGL32 Library
#include <gl\glu.h>   // Header File For The GLu32 Library
#include <gl\glaux.h> // Header File For The GLaux Library

class CTrail : public CParticleEngine  
{
public:
	void init();
	CTrail(int iNumParticles, CVector3 vecOrigin);
	virtual ~CTrail();
	void resetParticle(int i);										// Resets specific particle (with index i)
	void update(float fDT, float fThrust, CVector3 vecPos, 
		         CVector3 vecStart, CVector3 vecDistance, CVector3 vecUp, CVector3 vecRight,
					float fWidth, float fHeight);
	void update(float fDT);                        // Updates particle system
	void render(void);                                    // Render particles to the screen
	void render(float fThrust, CVector3 vecOrigin);                                    // Render particles to the screen
	void createParticle(int i, float fThrust, CVector3 vecHead, CVector3 vecOrigin, CVector3 vecUp, CVector3 vecRight,
					CVector3 vecPos, float fWidth, float fHeight);
	void reset();
private:
	CTexture *m_poTexture;
};

#endif // !defined(AFX_TRAIL_H__0572019F_F31B_441D_AFAE_4247EB700A35__INCLUDED_)
