// Brake.cpp: implementation of the CBrake class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Brake.h"
#include <stdlib.h>

#ifdef WIN32
  #include <windows.h>
#endif

#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBrake::CBrake(int iNumParticles, CVector3 vecOrigin)
{
	m_iNumParticles = iNumParticles;               // Set number of particles
	m_vecOrigin = vecOrigin;                           // Set origin of particles

	m_poParticles = new CParticle[m_iNumParticles];     // Create particle list
	m_iParticlesCreated = 0;
	srand( (unsigned)time( NULL ) );
}

CBrake::~CBrake()
{
	delete [] m_poParticles;
}

void CBrake::init()
{
	m_poTexture = new CTexture(1);

	char **astrFiles = new char*[1];

	astrFiles[0] = new char(16);
	strcpy(astrFiles[0], "smoke.png");

	m_poTexture->load(astrFiles, 1);
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
	
		m_poParticles[i].m_fr = 0.6f;
		m_poParticles[i].m_fg = 0.6f;
		m_poParticles[i].m_fb = 0.6f;

		m_poParticles[i].m_vecOldPosition = m_poParticles[i].m_vecPosition;
		//Sets the particles heading (see the update method)
		m_poParticles[i].m_vecAcceleration = vecHead + vecOrigin;
		//Set size

		fRandNum = RANDOM_FLOAT;
		m_poParticles[i].m_fSize = fRandNum * 0.1f ;

		//Set how long the particle will live (max 2 seconds)
		m_poParticles[i].m_fTimeToLive = 1.5f;

		m_poParticles[i].m_fAge = 0.0f;

}


void CBrake::render()
{
	CMatrix mat;
	float afCol[4];
	CVector3 vecUp, vecRight, vecBillboard1, vecBillboard2, vecTemp, vecTemp2, avecPlane[4];

	//First set up billboarding of the particles
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.m_afElement);
	vecRight.m_fx = mat.m_afElement[0];
	vecRight.m_fy = mat.m_afElement[4];
	vecRight.m_fz = mat.m_afElement[8];
	vecUp.m_fx    = mat.m_afElement[1];
	vecUp.m_fy    = mat.m_afElement[5];
	vecUp.m_fz    = mat.m_afElement[9];

	vecBillboard1 = vecRight + vecUp;
	vecBillboard2 = vecRight - vecUp;

	//Texture and blending stuff
	m_poTexture->setActive(0);
	glEnable(GL_BLEND);
	glDepthMask(GL_FALSE);

	glPushAttrib(GL_COLOR_MATERIAL);
	//then draw the particles
	glBegin(GL_QUADS);
		int iCount;
		for (iCount = 0 ; iCount < m_iParticlesCreated ; iCount++)
		{
			avecPlane[0] = m_poParticles[iCount].m_vecPosition - vecBillboard2 * m_poParticles[iCount].m_fSize;
			avecPlane[1] = m_poParticles[iCount].m_vecPosition + vecBillboard1 * m_poParticles[iCount].m_fSize;
			avecPlane[2] = m_poParticles[iCount].m_vecPosition + vecBillboard2 * m_poParticles[iCount].m_fSize;
			avecPlane[3] = m_poParticles[iCount].m_vecPosition - vecBillboard1 * m_poParticles[iCount].m_fSize;

			vecTemp = avecPlane[1] - avecPlane[0];
			vecTemp2 = avecPlane[3] - avecPlane[0];

			vecTemp2.cross(vecTemp);
			vecTemp2.unitize();

			glNormal3f(vecTemp2.m_fx, vecTemp2.m_fy, vecTemp2.m_fz);

			afCol[0] = m_poParticles[iCount].m_fr;
			afCol[1] = m_poParticles[iCount].m_fg;
			afCol[2] = m_poParticles[iCount].m_fb;
			afCol[3] = 0.4f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, afCol); 
			glColor4f(m_poParticles[iCount].m_fr, m_poParticles[iCount].m_fg, m_poParticles[iCount].m_fb, 0.3f);	

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

void CBrake::resetParticle(int i)
{

}

void CBrake::reset()
{
	memset ((void *)m_poParticles, 0, sizeof(CParticle) * m_iParticlesCreated);
	m_iParticlesCreated = 0;
}

