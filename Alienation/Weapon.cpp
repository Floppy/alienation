// Weapon.cpp: implementation of the CWeapon class.
//
//////////////////////////////////////////////////////////////////////

#include "Weapon.h"
#include "Physics1.h"

#ifdef WIN32
  #include <windows.h>
#endif
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
	FILE *fp;


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
	CMatrix mat;
	float afVec[4];
	CVector3 vecUp, vecRight, Billboard1, Billboard2, vecTemp, vecTemp2, avecPlane[4];

	//First set up billboarding of the particles
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.m_afElement);
	vecRight.m_fx = mat.m_afElement[0];
	vecRight.m_fy = mat.m_afElement[4];
	vecRight.m_fz = mat.m_afElement[8];
	vecUp.m_fx    = mat.m_afElement[1];
	vecUp.m_fy    = mat.m_afElement[5];
	vecUp.m_fz    = mat.m_afElement[9];

	Billboard1 = vecRight + vecUp;
	Billboard2 = vecRight - vecUp;

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
			avecPlane[0] = m_poParticles[iCount].m_vecPosition - Billboard2 * m_poParticles[iCount].m_fSize;
			avecPlane[1] = m_poParticles[iCount].m_vecPosition + Billboard1 * m_poParticles[iCount].m_fSize;
			avecPlane[2] = m_poParticles[iCount].m_vecPosition + Billboard2 * m_poParticles[iCount].m_fSize;
			avecPlane[3] = m_poParticles[iCount].m_vecPosition - Billboard1 * m_poParticles[iCount].m_fSize;

			vecTemp = avecPlane[1] - avecPlane[0];
			vecTemp2 = avecPlane[3] - avecPlane[0];

			vecTemp2.cross(vecTemp);
			vecTemp2.unitize();

			glNormal3f(vecTemp2.m_fx, vecTemp2.m_fy, vecTemp2.m_fz);

			afVec[0] = m_poParticles[iCount].m_fr;
			afVec[1] = m_poParticles[iCount].m_fg;
			afVec[2] = m_poParticles[iCount].m_fb;
			afVec[3] = 0.06f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, afVec); 
			glColor4f(m_poParticles[iCount].m_fr, m_poParticles[iCount].m_fg, m_poParticles[iCount].m_fb, 0.6f);	

			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(avecPlane[0].m_fx, avecPlane[0].m_fy, avecPlane[0].m_fz);

			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(avecPlane[1].m_fx, avecPlane[1].m_fy, avecPlane[1].m_fz);
			
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(avecPlane[2].m_fx, avecPlane[2].m_fy, avecPlane[2].m_fz);

			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(avecPlane[3].m_fx, avecPlane[3].m_fy, avecPlane[3].m_fz);
		
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
	strcpy(astrFiles[0], "ball.bmp");

	m_poTex->load("data/texture", astrFiles, 1);
}
