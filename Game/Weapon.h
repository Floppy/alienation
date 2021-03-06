// Weapon.h: interface for the CWeapon class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_WEAPON_H__553F0233_3E95_4D98_BA91_08582498967C__INCLUDED_)
#define AFX_WEAPON_H__553F0233_3E95_4D98_BA91_08582498967C__INCLUDED_

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <stdio.h>
#include "3D/ParticleEngine.h"
#include "3D/Texture.h"
#include "Math/Matrix.h"
#include "3D/Frustum.h"
#include "3D/Sprite.h"

class CWeapon : public CParticleEngine  
{
public:
	CWeapon(const CVector3& vecOrigin, float fSize, float fLifetime, float fSpeed, float fRate, const char* sound, const char* texture, const CRGBAColour& colour);
	virtual ~CWeapon();

	void resetParticle(int i);              // Resets specific particle (with index i)
	void update(float fDT);           // Updates particle system
	void update(float fDT, CVector3 vecHeading, CVector3 vecPos, float fSpeed, bool bFireHeld);           // Updates particle system
	void render(void) const;                      // Render particles to the screen
	void createParticle(int i, CVector3 vecHead, CVector3 vecPos, float fSpeed);
	void init();
        unsigned int m_uiTexture;
        float m_fSize;
        float m_fLifetime;
        float m_fSpeed;
	float m_fFireRate;
	float m_fTimeSinceLast;
	bool m_abEmpty[100];
private:
        mutable CSprite m_oSprite;
   mutable CFrustum m_oFrustum;
   unsigned int m_uiSoundEffect;

};

#endif // !defined(AFX_WEAPON_H__553F0233_3E95_4D98_BA91_08582498967C__INCLUDED_)
