// Weapon.cpp: implementation of the CWeapon class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Weapon.h"
#include "Physics/Physics1.h"

#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWeapon::CWeapon(int iNumParticles, CVector3 vecOrigin)
{
	m_iNumParticles = iNumParticles;               // Set number of particles
	m_vecOrigin = vecOrigin;                           // Set origin of particles

	m_poParticles = new CParticle[m_iNumParticles];     // Create particle list
	m_iParticlesCreated = 0;
	m_fFireRate = 0.5f;
	m_fTimeSinceLast = 0.5f;
	m_poTex = new CTexture(1);
	int i;
	for (i = 0; i < 100 ; i++)
		m_abEmpty[i] = true;
}

CWeapon::~CWeapon()
{

}

void CWeapon::reset(void)
{
	memset((void *)m_poParticles, 0, sizeof(CParticle) * m_iNumParticles);
	m_iParticlesCreated = 0;
}

void CWeapon::resetParticle(int i)
{
	m_poParticles[i].m_vecPosition = CVector3(0.0f, 0.0f, 0.0f);
	
	m_poParticles[i].m_fr = 0.0f;
	m_poParticles[i].m_fg = 0.0f;
	m_poParticles[i].m_fb = 0.0f;

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
	
	m_poParticles[i].m_fr = 1.0f;
	m_poParticles[i].m_fg = 0.2f;
	m_poParticles[i].m_fb = 0.4f;

	m_poParticles[i].m_vecOldPosition = m_poParticles[i].m_vecPosition;
	//Sets the particles heading (see the update method)
	m_poParticles[i].m_vecAcceleration = vecHead;
	//Set size
	m_poParticles[i].m_fSize = 1.0f ;

	m_poParticles[i].m_fTimeToLive = 7.0f;

	m_poParticles[i].m_fAge = 0.0f;

	m_poParticles[i].m_fSpeed = 235.0f;
}

void CWeapon::render(void)
{
	float afMaterial[4];

	//Texture and blending stuff
	m_poTex->setActive(0);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);
	glPushAttrib(GL_COLOR_MATERIAL);

	//then draw the particles
	glBegin(GL_QUADS);
		int iCount;
		for (iCount = 0 ; iCount < m_iParticlesCreated ; iCount++)
		{
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
	glEnd();
	glPopAttrib();
	glDepthMask(GL_TRUE); 
	glDisable(GL_BLEND);
}

void CWeapon::init()
{
	char **astrFiles = new char*[1];

	astrFiles[0] = new char(16);
	strcpy(astrFiles[0], "ball.png");

	m_poTex->load(astrFiles, 1);
}

void CWeapon::renderBillboard(CVector3 oPos, float fSize, float* pfMaterial)
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