// Stars.cpp: implementation of the CStars class.
//
//////////////////////////////////////////////////////////////////////

#include "Stars.h"
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
	CMatrix mat;
	CVector3 vecRight, vecUp, vecBillboard1, vecBillboard2, vecTemp;

	glGetFloatv(GL_MODELVIEW_MATRIX, mat.m_afElement);
	vecRight.m_fx = mat.m_afElement[0];
	vecRight.m_fy = mat.m_afElement[4];
	vecRight.m_fz = mat.m_afElement[8];
	vecUp.m_fx    = mat.m_afElement[1];
	vecUp.m_fy    = mat.m_afElement[5];
	vecUp.m_fz    = mat.m_afElement[9];

	vecBillboard1 = vecRight + vecUp;
	vecBillboard2 = vecRight - vecUp;

	glPushMatrix();
	glTranslatef(vecPos.m_fx, vecPos.m_fy, vecPos.m_fz);

	glEnable(GL_BLEND);

	m_poTexture->setActive(0);

//	glBindTexture(GL_TEXTURE_2D, texture[0]);
	int iCount;
	glBegin(GL_QUADS);
		for (iCount = 0 ; iCount < m_iNumStars ; iCount++)
		{
			glColor4f(m_aoStars[iCount].m_vecColor.m_fx, m_aoStars[iCount].m_vecColor.m_fy, m_aoStars[iCount].m_vecColor.m_fz, 0.3f);
			vecTemp = m_aoStars[iCount].m_vecPos;
			vecTemp.unitize();

			vecTemp += m_aoStars[iCount].m_vecPos;
			vecTemp *= -1;

			glNormal3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);

			vecTemp = m_aoStars[iCount].m_vecPos - vecBillboard2 * m_aoStars[iCount].m_fSize;
			glTexCoord2f(0.0f, 1.0f);
			glVertex3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);

			vecTemp = m_aoStars[iCount].m_vecPos + vecBillboard1 * m_aoStars[iCount].m_fSize;
			glTexCoord2f(1.0f, 1.0f);
			glVertex3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);
			
			vecTemp = m_aoStars[iCount].m_vecPos + vecBillboard2 * m_aoStars[iCount].m_fSize;
			glTexCoord2f(1.0f, 0.0f);
			glVertex3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);

			vecTemp = m_aoStars[iCount].m_vecPos - vecBillboard1 * m_aoStars[iCount].m_fSize;
			glTexCoord2f(0.0f, 0.0f);
			glVertex3f(vecTemp.m_fx, vecTemp.m_fy, vecTemp.m_fz);
		
		}
	glEnd();
	
	glPopMatrix();
	
	glDisable(GL_BLEND);
}

