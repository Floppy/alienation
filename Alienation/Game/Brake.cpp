// Brake.cpp: implementation of the CBrake class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Brake.h"
#include <stdlib.h>
#include "3D/TextureManager.h"
#include "3D/Material.h"
#include "Math/Random.h"

#ifdef WIN32
  #include <windows.h>
#endif

#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBrake::CBrake(int iNumParticles, CVector3 vecOrigin) :
   m_uiTexture(0)
{
	m_iNumParticles = iNumParticles;               // Set number of particles
	m_vecOrigin = vecOrigin;                           // Set origin of particles

	m_poParticles = new CParticle[m_iNumParticles];     // Create particle list
	m_iParticlesCreated = 0;
	randomSeed( (unsigned)time( NULL ) );
}

CBrake::~CBrake()
{
   delete [] m_poParticles;
   g_oTextureManager.removeReference(m_uiTexture);
}

void CBrake::init()
{
   // Create sprite
   CMaterial oMaterial;
   oMaterial.m_oDiffuse = CRGBAColour(0.5f, 0.5f, 0.5f,0);
   oMaterial.m_uiTexture = g_oTextureManager.load("smoke.png");   
   m_oSprite = CSprite(oMaterial);
   m_oSprite.init();   
}

void CBrake::update(float fDT)
{

}

// Updates the particles. 
// timepassed = time passed since last update in seconds
// thrust = the ships thrust
// pos = the position of the ship
// start = the trails start position
void CBrake::update(float fDT, CVector3 vecPos, CVector3 vecHead, CVector3 vecStart, bool bKeyDown)
{
	CVector3 vecSpeed, vecTemp;

	CVector3 vecTHead = vecStart - vecPos;

	//if no thrust then reset the array and exit
	if (! bKeyDown)
	{
		reset();
		return;
	}

	int iCount;
	for (iCount = 0 ; iCount < m_iParticlesCreated ; iCount++ ) //for each particle
	{
		//update the particles age, and if too old, create it again
			
		m_poParticles[iCount].m_fAge += fDT;
		if (m_poParticles[iCount].m_fAge > m_poParticles[iCount].m_fTimeToLive)
		{
			createParticle(iCount, vecTHead, vecStart);
		}
		else
		{
			//calculate the speed based on the acceleration (itself calculated
			//from the above thead vector)
			vecSpeed = (m_poParticles[iCount].m_vecAcceleration * 0.2f) * fDT;
			m_poParticles[iCount].m_vecPosition += vecSpeed;// get the new position
		}
	}

	//Not the maximum created? (confusing variable names, whoops)
	if (m_iParticlesCreated < m_iNumParticles)
	{
		//Create a new one and update the particle count
		createParticle(iCount, vecTHead, vecStart);
		m_iParticlesCreated ++;
	}
}

void CBrake::createParticle(int i, CVector3 vecHead, CVector3 vecOrigin)
{


	CVector3 vecTemp1, vecTemp2;
	float fRandNum;

		m_poParticles[i].m_vecPosition = vecOrigin;
	
		m_poParticles[i].m_vecOldPosition = m_poParticles[i].m_vecPosition;
		//Sets the particles heading (see the update method)
		m_poParticles[i].m_vecAcceleration = vecHead + vecOrigin;
		//Set size

		fRandNum = random01();
		m_poParticles[i].m_fSize = fRandNum * 0.1f ;

		//Set how long the particle will live (max 2 seconds)
		m_poParticles[i].m_fTimeToLive = 1.5f;

		m_poParticles[i].m_fAge = 0.0f;

}


void CBrake::render()
{
	//Texture and blending stuff
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

        for (int iCount = 0 ; iCount < m_iParticlesCreated ; iCount++)
        {
           // Set size
           m_oSprite.setSize(m_poParticles[iCount].m_fSize);
           // Set position
           m_oSprite.setTranslation(m_poParticles[iCount].m_vecPosition);
           // Render
           m_oSprite.render();
        }

	glDepthMask(GL_TRUE); 
	glDisable(GL_BLEND);
}

void CBrake::resetParticle(int i)
{

}

void CBrake::reset()
{
	memset ((void *)m_poParticles, 0, sizeof(CParticle) * m_iParticlesCreated);
	m_iParticlesCreated = 0;
}

