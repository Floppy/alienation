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

   // Draw exhaust flare
   if (m_oFrustum.PointInFrustum(vecOrigin.m_fx, vecOrigin.m_fy, vecOrigin.m_fz))
   {
      // Bind Texture
      g_oTextureManager.activate(m_auiTextures[1]);
      // Get material
      afMaterial[0] = 1.0f;
      afMaterial[1] = 1.0f;
      afMaterial[2] = 1.0f;
      afMaterial[3] = 0.05f;
      // Calculate engine flare size
      float fSize = fThrust * 0.0005f;
      if (fSize > 2.5f) fSize = 2.5f;
      // Render
      renderBillboard(vecOrigin,fSize,afMaterial);
   }
   // Draw trail

   // Bind Texture
   g_oTextureManager.activate(m_auiTextures[0]);
   // Draw each particle
   for (int iCount = 0 ; iCount < m_iParticlesCreated ; iCount++)
   {
      // Get material
      if (m_oFrustum.PointInFrustum(m_poParticles[iCount].m_vecPosition.m_fx, 
									m_poParticles[iCount].m_vecPosition.m_fy, 
									m_poParticles[iCount].m_vecPosition.m_fz))
	  {
		 afMaterial[0] = m_poParticles[iCount].m_fr;
		 afMaterial[1] = m_poParticles[iCount].m_fg;
		 afMaterial[2] = m_poParticles[iCount].m_fb;
		 afMaterial[3] = 0.03f;
		 // Render
		 renderBillboard(m_poParticles[iCount].m_vecPosition, m_poParticles[iCount].m_fSize,afMaterial);
	  }
   }

   // Restore state
   glPopAttrib();

   // Disable alpha blend
   glDepthMask(GL_TRUE); 
   glDisable(GL_BLEND);
}

void CTrail::renderBillboard(CVector3 oPos, float fSize, float* pfMaterial)
{
   // Save matrix state
   glPushMatrix();
   // Move to particle position
   glTranslatef(oPos.m_fx, oPos.m_fy, oPos.m_fz);
   
   // Get matrix
   float afMatrix[16];
   glGetFloatv(GL_MODELVIEW_MATRIX, afMatrix);

   // Get normal
   CVector3 vecNormal;
   vecNormal.m_fx = -afMatrix[2];
   vecNormal.m_fy = -afMatrix[6];
   vecNormal.m_fz = -afMatrix[10];

   // Remove rotation from model/view matrix
   afMatrix[0] = afMatrix[5] = afMatrix[10] = afMatrix[11] = 1.0f;
   afMatrix[1] = afMatrix[2] = afMatrix[3] = afMatrix[4] = 0.0f;
   afMatrix[6] = afMatrix[7] = afMatrix[8] = afMatrix[9] = 0.0f;
   glLoadMatrixf(afMatrix);
   
   // Draw billboard
   glBegin(GL_QUADS);      

   // Material
   glMaterialfv(GL_FRONT, GL_AMBIENT, pfMaterial);
   // Normal
   glNormal3f(vecNormal.m_fx, vecNormal.m_fy, vecNormal.m_fz);

   // Vertices
   for (int i=0; i<2; i++) 
   {
      for (int j=0; j<2; j++) 
      {
         glTexCoord2f( ( i==j ? 0.0f : 1.0f ) , ( i==0 ? 1.0f : 0.0f ) );
         glVertex3f( ( i==j ? -fSize : fSize ) , ( i==0 ? fSize : -fSize ), 0.0f );
      }
   }
   // Finish quad
   glEnd();
   // Restore matrix state
   glPopMatrix();
   // Done
   return;
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
	vecTemp.unitize();

	fNum = RANDOM_FLOAT;
	m_poParticles[i].m_vecPosition += vecTemp * (fNum * 4.5f);

	vecTemp.m_fx = m_poParticles[i].m_vecPosition.m_fx - vecOrigin.m_fx;
	vecTemp.m_fy = m_poParticles[i].m_vecPosition.m_fy - vecOrigin.m_fy;
	vecTemp.m_fz = 0.0f;

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

}

void CTrail::init()
{
   m_auiTextures[0] = g_oTextureManager.load("star.png");
   m_auiTextures[1] = g_oTextureManager.load("flare.png");
}
