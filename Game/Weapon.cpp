
// Weapon.cpp: implementation of the CWeapon class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Weapon.h"
#include "Physics/Physics1.h"
#include "3D/TextureManager.h"
#include "Sound/SoundManager.h"
#include <SDL_opengl.h>

using namespace NSDSound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeapon::CWeapon(const CVector3& vecOrigin, float fSize, float fLifetime, float fSpeed, float fRate, const char* sound, const char* texture, const CRGBAColour& colour) :
   CParticleEngine(100, vecOrigin),
   m_fSize(fSize),
   m_fLifetime(fLifetime),
   m_fSpeed(fSpeed),
   m_fFireRate(fRate),
   m_fTimeSinceLast(fRate),
   m_uiSoundEffect(-1)
{
   int i;
   for (i = 0; i < 100 ; i++)
      m_abEmpty[i] = true;

   // Load sound
   m_uiSoundEffect = g_oSoundManager.load(sound);

   // Set material
   CMaterial oMaterial;
   oMaterial.m_oEmissive = colour;
   oMaterial.m_oAmbient = colour;
   oMaterial.m_oDiffuse = colour;
   oMaterial.m_uiTexture = g_oTextureManager.load(texture);
   m_oSprite.setMaterial(oMaterial);

}

   

CWeapon::~CWeapon()
{
   g_oTextureManager.removeReference(m_uiTexture);
}

void CWeapon::resetParticle(int i)
{
	m_poParticles[i].m_vecPosition = CVector3(0.0f, 0.0f, 0.0f);
	
	m_poParticles[i].m_vecOldPosition = CVector3(0.0f, 0.0f, 0.0f);
	//Sets the m_poParticles heading (see the update method)
	m_poParticles[i].m_vecAcceleration = CVector3(0.0f, 0.0f, 0.0f);
	//Set size
	m_poParticles[i].m_fSize = 0.0f ;

	m_poParticles[i].m_fTimeToLive = 0.0f;

	m_poParticles[i].m_fAge = 0.0f;

	m_poParticles[i].m_fSpeed = 0.0f;	
}

void CWeapon::update(float timepassed)
{
	
}

void CWeapon::update(float fDT, CVector3 vecHeading, CVector3 vecPos, float fSpeed, bool bFireHeld)
{
	CVector3 vecVel, vecTemp1;
	int iEmp = -1;


	if (!bFireHeld && m_iParticlesCreated == 0)
	{
		reset();
		return;
	}

	m_fTimeSinceLast += fDT;
	int iCount;
	for (iCount = 0 ; iCount < m_iNumParticles ; iCount++ ) //for each particle
	{
		if (!m_abEmpty[iCount])
		{
			//update the m_poParticles age, and if too old, create it again
			
			m_poParticles[iCount].m_fAge += fDT;
			if (m_poParticles[iCount].m_fAge > m_poParticles[iCount].m_fTimeToLive)
			{
//				resetParticle(iCount);
				m_abEmpty[iCount] = true;
				m_iParticlesCreated --;
				if (m_iParticlesCreated == 0)
				{
					reset();
					int i;
					for (i = 0 ; i < 100 ; i ++ )
					{
						m_abEmpty[i] = true;
					}
				}
			}
			else
			{
				//calculate the speed based on the acceleration (itself calculated
				//from the above thead vector)
				vecVel = (m_poParticles[iCount].m_vecAcceleration * m_poParticles[iCount].m_fSpeed) * fDT;
				m_poParticles[iCount].m_vecPosition += vecVel;// get the new position
			}
		}
	}

	//Not the maximum created? (confusing variable names, whoops)
	if (m_iParticlesCreated < m_iNumParticles)
	{
		if (m_fTimeSinceLast > m_fFireRate)
		{
			if (bFireHeld)
			{
				for (iCount = 0 ; iCount < m_iNumParticles ; iCount ++)
				{
					if (m_abEmpty[iCount])
					{
						iEmp = iCount;
						break;
					}
				}
				if (iEmp != -1)
				{
					//Create a new one and update the particle iCount
					createParticle(iEmp, vecHeading, vecPos, fSpeed);
					m_abEmpty[iEmp] = false;
					m_iParticlesCreated ++;
					m_fTimeSinceLast = 0.0;
				}
			}
		}
	}
	
}

void CWeapon::createParticle(int i, CVector3 vecHead, CVector3 vecPos, float fSpeed)
{

	m_poParticles[i].m_vecPosition = vecPos;
	//Calculate the starting position, based on the start variable
	//Very basic, needs updating really, does for now th0
	
	m_poParticles[i].m_vecOldPosition = m_poParticles[i].m_vecPosition;
	//Sets the particles heading (see the update method)
	m_poParticles[i].m_vecAcceleration = vecHead;
	//Set size
	m_poParticles[i].m_fSize = m_fSize;
	m_poParticles[i].m_fTimeToLive = m_fLifetime;
	m_poParticles[i].m_fSpeed = m_fSpeed;
	m_poParticles[i].m_fAge = 0.0f;

        //Play sound whenever we create a particle
        int iChannel = g_oSoundManager.play(m_uiSoundEffect);
        if (iChannel != -1) g_oSoundManager.setChannelLocation(iChannel,vecPos);
        

}

void CWeapon::render(void) const
{
	//Texture and blending stuff
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//then draw the particles
        for (int iCount = 0 ; iCount < m_iParticlesCreated ; iCount++)
        {
           if (m_oFrustum.PointInFrustum(m_poParticles[iCount].m_vecPosition))
           {
              // Set position
              m_oSprite.setTranslation(m_poParticles[iCount].m_vecPosition);
              // Draw
              m_oSprite.render();
           }
        }

        // Tidy up
	glDepthMask(GL_TRUE); 
	glDisable(GL_BLEND);
}

void CWeapon::init()
{
   m_oSprite.init();
}
