// Trail.h: interface for the CTrail class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRAIL_H__0572019F_F31B_441D_AFAE_4247EB700A35__INCLUDED_)
#define AFX_TRAIL_H__0572019F_F31B_441D_AFAE_4247EB700A35__INCLUDED_

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3D/ParticleEngine.h"
#include <stdio.h>
#include <time.h>
#include "Math/Vector.h"
#include "3D/Texture.h"
#include "Math/Matrix.h"
#include "3D/Frustum.h"
#include "3D/Sprite.h"

class CTrail : public CParticleEngine  
{
public:
	
	void init();
	CTrail();
	CTrail(int iNumParticles, CVector3 vecOrigin);
	virtual ~CTrail();
	void resetParticle(int i);										// Resets specific particle (with index i)
	void update(float fDT, float fThrust, CVector3 vecPos, 
		         CVector3 vecStart, CVector3 vecDistance, CVector3 vecUp, CVector3 vecRight,
					float fWidth, float fHeight);
	void render(void) const;                                    // Render particles to the screen
	void createParticle(int i, float fThrust, CVector3 vecHead, CVector3 vecOrigin, CVector3 vecUp, CVector3 vecRight,
					CVector3 vecPos, float fWidth, float fHeight);
        /**
         * Initialise engine flare sprite.
         */ 
        void setFlare(const char* strTexture, CRGBAColour oCol, float fSize);

        /**
         * Initialise trail sprite.
         */
        void setTrail(const char* strTexture, CRGBAColour oCol, float fSize);

private:

	void update(float fDT) {}                        // Updates particle system

        /**
         * Engine flare geometry
         */
        CSprite m_oFlare;

        /**
         * Trail particle geometry
         */
        mutable CSprite m_oTrail;

        /**
         * View frustum for culling.
         */
	mutable CFrustum m_oFrustum;

        /**
         * Texture IDs
         */
	unsigned int m_auiTextures[2];

        /** 
         * Maximum flare size.
         */
        float m_fMaxFlareSize;

};

#endif // !defined(AFX_TRAIL_H__0572019F_F31B_441D_AFAE_4247EB700A35__INCLUDED_)
