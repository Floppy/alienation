// Stars.cpp: implementation of the CStars class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Stars.h"
#include <stdlib.h>

#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStars::CStars() :
	m_poTexture(NULL)
{}

CStars::~CStars()
{
	delete m_poTexture;
}

void CStars::initStars()
{
	float fy, fp;
	CQuat quaTemp;
	CMatrix mat;
	CVector3 vecPos;
	int i;

	m_poTexture = new CTexture(3);
	m_iNumStars = 500;
	for (i = 0; i < 500; i++)
	{
		fy = RANDOM_FLOAT * 360;
		fp = RANDOM_FLOAT * 360;
		quaTemp.eulerToQuat(fy * piover180, 0.0f, fp * piover180);
		mat.QuatToMatrix(quaTemp);	
		vecPos = CVector3(0.0f, 0.0f, -1.0f);
		m_aoStars[i].m_vecPos = mat.MultMatrixVector(vecPos);
		m_aoStars[i].m_vecPos *= 9000.0f;
		m_aoStars[i].m_iTexture = 0;
		
		fy = RANDOM_FLOAT;
		if (fy < 0.33f)
		{
			m_aoStars[i].m_fSize = 15.0f;
		}
		else
		{
			if (fy < 0.66f)
			{
				m_aoStars[i].m_fSize = 25.0f;
			}
			else
			{
				m_aoStars[i].m_fSize = 35.0f;
			}
		}
		m_aoStars[i].m_vecColor.m_fx = RANDOM_FLOAT;
		m_aoStars[i].m_vecColor.m_fy = RANDOM_FLOAT;
		m_aoStars[i].m_vecColor.m_fz = RANDOM_FLOAT;
	}
	char **astrFiles = new char*[3];

	astrFiles[0] = new char(16);
	strcpy(astrFiles[0], "an01.png");
	astrFiles[1] = new char(16);
	strcpy(astrFiles[1], "an02.png");
	astrFiles[2] = new char(16);
	strcpy(astrFiles[2], "an03.png");

	m_poTexture->load(astrFiles, 3);

//	LoadGLTextures();
}

void CStars::draw(CVector3 vecPos)
{

	glPushMatrix();
	glTranslatef(vecPos.m_fx, vecPos.m_fy, vecPos.m_fz);

	glEnable(GL_BLEND);

	m_poTexture->setActive(0);

//	glBindTexture(GL_TEXTURE_2D, texture[0]);
	int iCount;
	glBegin(GL_QUADS);
		for (iCount = 0 ; iCount < m_iNumStars ; iCount++)
		{
		    if (m_oFrustum.PointInFrustum(m_aoStars[iCount].m_vecPos.m_fx,
										  m_aoStars[iCount].m_vecPos.m_fy,
										  m_aoStars[iCount].m_vecPos.m_fz))
			{
			   glColor4f(m_aoStars[iCount].m_vecColor.m_fx, m_aoStars[iCount].m_vecColor.m_fy, m_aoStars[iCount].m_vecColor.m_fz, 0.3f);
			   renderBillboard(m_aoStars[iCount].m_vecPos, m_aoStars[iCount].m_fSize);		

			}
		}
	glEnd();
	
	glPopMatrix();
	
	glDisable(GL_BLEND);
}

void CStars::renderBillboard(CVector3 oPos, float fSize)
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