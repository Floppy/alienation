// Trail.cpp: implementation of the CTrail class.
//
//////////////////////////////////////////////////////////////////////

#include "Trail.h"
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
			vecSpeed = ((m_poParticles[iCount].m_vecAcceleration * 0.4f) * fDT);
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
			createParticle(iCount, fThrust, vecTHead, vecStart, vecUp, vecRight, vecPos, fWidth, fHeight);
			m_iParticlesCreated ++;
		}
	}

}

void CTrail::render(void)
{

}

void CTrail::render(float fThrust, CVector3 vecOrigin)
{
	CMatrix mat;
	float afVec[4];
	CVector3 vecUp, vecRight, vecBillboard1, vecBillboard2, vecTemp, vecTemp2, avecPlane[4];
	float fSize = 0.0005f * fThrust;
	if (fSize > 2.5f)
		fSize = 2.5f;

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

			afVec[0] = m_poParticles[iCount].m_fr;
			afVec[1] = m_poParticles[iCount].m_fg;
			afVec[2] = m_poParticles[iCount].m_fb;
			afVec[3] = 0.03f;
			glMaterialfv(GL_FRONT, GL_AMBIENT, afVec); 
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
	afVec[0] = 1.0f;
	afVec[1] = 1.0f;
	afVec[2] = 1.0f;
	afVec[3] = 0.05f;
	glMaterialfv(GL_FRONT, GL_AMBIENT, afVec); 
	m_poTexture->setActive(1);
//	glBindTexture(GL_TEXTURE_2D, texture[1]);
	glBegin(GL_QUADS);

		glColor4f(1.0f, 1.0f, 1.0f, 0.5f);	
		
		vecTemp = vecOrigin - vecBillboard2 * fSize;
		glTexCoord2f(0.0f, 1.0f);
		glVertex3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);

		vecTemp = vecOrigin + vecBillboard1 * fSize;
		glTexCoord2f(1.0f, 1.0f);
		glVertex3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);
			
		vecTemp = vecOrigin + vecBillboard2 * fSize;
		glTexCoord2f(1.0f, 0.0f);
		glVertex3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);

		vecTemp = vecOrigin - vecBillboard1 * fSize;
		glTexCoord2f(0.0f, 0.0f);
		glVertex3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);
		
	glEnd();
	glPopAttrib();
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
	m_poTexture = new CTexture(2);

	char **astrFiles = new char*[2];

	astrFiles[0] = new char(16);
	strcpy(astrFiles[0], "star.png");
	astrFiles[1] = new char(16);
	strcpy(astrFiles[1], "flare.png");

	m_poTexture->load(astrFiles, 2);
}
