// Brake.cpp: implementation of the CBrake class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Brake.h"
#include <stdlib.h>
#include "3D/TextureManager.h"
#include "3D/Material.h"

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
	srand( (unsigned)time( NULL ) );
}

CBrake::~CBrake()
{
   delete [] m_poParticles;
   g_oTextureManager.removeReference(m_uiTexture);
}

void CBrake::init()
{
   m_uiTexture = g_oTextureManager.load("smoke.png");
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
	CVector3 vecBillboard1, vecBillboard2, vecTemp, vecTemp2, avecPlane[4];

	//First set up billboarding of the particles
	glGetFloatv(GL_MODELVIEW_MATRIX, mat.m_afElement);
        
        CVector3 vecRight(mat.m_afElement[0],mat.m_afElement[4],mat.m_afElement[8]);
        CVector3 vecUp(mat.m_afElement[1],mat.m_afElement[5],mat.m_afElement[9]);

	vecBillboard1 = vecRight + vecUp;
	vecBillboard2 = vecRight - vecUp;

	//Texture and blending stuff
	g_oTextureManager.activate(m_uiTexture);
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
			vecTemp2.normalise();

			glNormal3fv(vecTemp2.glVector());

			CRGBAColour colour(m_poParticles[iCount].m_fr,m_poParticles[iCount].m_fg,m_poParticles[iCount].m_fb,0.4f);
			glMaterialfv(GL_FRONT, GL_AMBIENT, colour.glColour()); 
			glColor4f(m_poParticles[iCount].m_fr, m_poParticles[iCount].m_fg, m_poParticles[iCount].m_fb, 0.3f);	

			glTexCoord2f(0.0f, 1.0f);
			glVertex3fv(avecPlane[0].glVector());

			glTexCoord2f(1.0f, 1.0f);
			glVertex3fv(avecPlane[1].glVector());
			
			glTexCoord2f(1.0f, 0.0f);
			glVertex3fv(avecPlane[2].glVector());

			glTexCoord2f(0.0f, 0.0f);
			glVertex3fv(avecPlane[3].glVector());
		
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

