// Trail.cpp: implementation of the CTrail class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Trail.h"
#include "3D/TextureManager.h"
#include <stdlib.h>
#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTrail::CTrail(int iNumParticles, CVector3 vecOrigin)
{
	m_iNumParticles = iNumParticles;               // Set number of particles
	m_vecOrigin = vecOrigin;                           // Set origin of particles

	m_poParticles = new CParticle[m_iNumParticles];     // Create particle list
	m_iParticlesCreated = 0;
	srand( (unsigned)time( NULL ) );

}

CTrail::~CTrail()
{
   delete [] m_poParticles;
   for (int i=0; i<2; i++) {
      g_oTextureManager.removeReference(m_auiTextures[i]);
   }
}

void CTrail::update(float timepassed)
{

}

// Updates the particles. 
// timepassed = time passed since last update in seconds
// thrust = the ships thrust
// pos = the position of the ship
// start = the trails start position
void CTrail::update(float fDT, float fThrust, CVector3 vecPos, CVector3 vecStart, CVector3 vecDistance, CVector3 vecUp, CVector3 vecRight,
					float fWidth, float fHeight)
{
	CVector3 vecSpeed, vecTemp;

	//Create a heading for any new particles created this update
	// The start vector is the position of the of the origin of the 
	//particles on the ship itself. It is rotated along with the ships
	//heading vector (in fact created from it.And as you can see, the 
	//particles always start from the correct position, so it should be
	//ok. It is multiplied by the thrust scaler (tho scaled sown a bit as it
	//goes up to 5000!
	CVector3 vecTHead = vecStart - vecPos;
	vecTHead *= fThrust/2000.0f;
	vecTHead += vecPos;

	//if no thrust then reset the array and exit
	if (fThrust == 0.0f)
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
			createParticle(iCount, fThrust, vecTHead, vecStart, vecUp, vecRight, vecPos, fWidth, fHeight);
		}
		else
		{
			//calculate the speed based on the acceleration (itself calculated
			//from the above thead vector)
			vecSpeed = ((m_poParticles[iCount].m_vecAcceleration * 0.2f) * fDT);
			vecSpeed += vecDistance;
			m_poParticles[iCount].m_vecPosition += vecSpeed;// get the new position
			m_poParticles[iCount].m_fSize -= 0.001f;
		}
	}

	//Not the maximum created? (confusing variable names, whoops)
	if (m_iParticlesCreated < m_iNumParticles - 5)
	{
		for (iCount = 0 ; iCount < 5 ; iCount++)
		{
			//Create a new one and update the particle iCount
			createParticle(m_iParticlesCreated, fThrust, vecTHead, vecStart, vecUp, vecRight, vecPos, fWidth, fHeight);
			m_iParticlesCreated ++;
		}
	}

}

void CTrail::render(void)
{

}

void CTrail::render(float fThrust, CVector3 vecOrigin)
{
   // Material
   float afMaterial[4];

   // Enable alpha blend
   glEnable(GL_BLEND);
   glDepthMask(GL_FALSE);

   // Save state
   glPushAttrib(GL_COLOR_MATERIAL);

   // Draw engine flare
   if (m_oFrustum.PointInFrustum(vecOrigin)) {
      // Calculate engine flare size
      float fSize = fThrust * 0.0005f;
      if (fSize > 2.5f) fSize = 2.5f;
      m_oFlare.setSize(fSize);
      // Set location
      m_oFlare.setTranslation(vecOrigin);
      // Draw exhaust flare
      m_oFlare.render();
   }

   // Draw trail
   for (int iCount = 0 ; iCount < m_iParticlesCreated ; iCount++)
   {
      if (m_oFrustum.PointInFrustum(m_poParticles[iCount].m_vecPosition)) {
         // Set location
         m_oTrail.setTranslation(m_poParticles[iCount].m_vecPosition);
         // Draw flare
         m_poParticles[iCount].getGeometry()->render();
      }
   }
   
   // Restore state
   glPopAttrib();

   // Disable alpha blend
   glDepthMask(GL_TRUE); 
   glDisable(GL_BLEND);
}


void CTrail::resetParticle(int i)
{

}

void CTrail::reset()
{
	memset ((void *)m_poParticles, 0, sizeof(CParticle) * m_iParticlesCreated);
	m_iParticlesCreated = 0;
}




void CTrail::createParticle(int i, float fThrust, CVector3 vecHead, CVector3 vecOrigin, CVector3 vecUp, CVector3 vecRight,
					CVector3 vecPos, float fWidth, float fHeight)
{
//	srand( (unsigned)time( NULL ) );

	float fNum = RANDOM_FLOAT;

	CVector3 vecTemp, vecTemp1, vecTemp2;

	m_poParticles[i].m_vecPosition = vecOrigin;
	//Calculate the starting position, based on the start variable
	//Very basic, needs updating really, does for now th0
	
	vecTemp = vecUp * fHeight;

	if (fNum > 0.5f)
	{	
		vecTemp1 = vecTemp * (fNum - 0.5f);
		m_poParticles[i].m_vecPosition += vecTemp1;
	}
	else
	{
		vecTemp1 = vecTemp * fNum;
		m_poParticles[i].m_vecPosition -= vecTemp1;
	}

	vecTemp = vecRight * fWidth;

	fNum = RANDOM_FLOAT;
	if (fNum > 0.5f)
	{	
		vecTemp2 = vecTemp * (fNum - 0.5f);
		m_poParticles[i].m_vecPosition += vecTemp2;
	}
	else
	{
		vecTemp2 = vecTemp * fNum;
		m_poParticles[i].m_vecPosition -= vecTemp2;
	}

	vecTemp = vecOrigin - vecPos;
	vecTemp.normalise();

	fNum = RANDOM_FLOAT;
	m_poParticles[i].m_vecPosition += vecTemp * (fNum * 4.5f);

	vecTemp.X() = m_poParticles[i].m_vecPosition.X() - vecOrigin.X();
	vecTemp.Y() = m_poParticles[i].m_vecPosition.Y() - vecOrigin.Y();
	vecTemp.Z() = 0.0f;

	m_poParticles[i].m_fr = 1.0f - vecTemp.length();
	m_poParticles[i].m_fg = m_poParticles[i].m_fr;
	m_poParticles[i].m_fb = m_poParticles[i].m_fr / 4;

	m_poParticles[i].m_vecOldPosition = m_poParticles[i].m_vecPosition;
	//Sets the m_poParticles heading (see the update method)
	m_poParticles[i].m_vecAcceleration = vecHead - m_poParticles[i].m_vecPosition;
	//Set size
	fNum = RANDOM_FLOAT;
	m_poParticles[i].m_fSize = 1.0f ;

	//Set how long the particle will live (max 2 seconds)
	fNum = RANDOM_FLOAT;
	m_poParticles[i].m_fTimeToLive = fNum * (fThrust / 2000);

	m_poParticles[i].m_fAge = 0.0f;

        m_poParticles[i].setGeometry(&m_oTrail);

}

void CTrail::init()
{
   // Create trail particle geometry
   CMaterial oTrailMaterial;
   oTrailMaterial.m_oDiffuse = CRGBAColour(255,255,64,0);
   oTrailMaterial.m_uiTexture = g_oTextureManager.load("star.png");   
   m_oTrail = CSprite(oTrailMaterial);
   m_oTrail.init();

   // Create engine flare
   CMaterial oFlareMaterial;
   oFlareMaterial.m_oDiffuse = CRGBAColour(255, 255, 255, 0);
   oFlareMaterial.m_uiTexture = g_oTextureManager.load("flare.png");
   m_oFlare = CSprite(oFlareMaterial);
   m_oFlare.init();
}
