// Stars.cpp: implementation of the CStars class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Stars.h"
#include <stdlib.h>
#include <SDL_opengl.h>
#include "3D/TextureManager.h"
#include "Math/Random.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStars::CStars()
{
}

CStars::~CStars()
{
   for (int i=0; i<3; i++) {
      g_oTextureManager.removeReference(m_auiTextures[i]);
   }
}

void CStars::initStars()
{
	float fy, fp;
	CVector3 vecPos;
	int i;

	m_iNumStars = 500;
	for (i = 0; i < 500; i++)
	{
		fy = random01() * 360;
		fp = random01() * 360;
		CQuat quaTemp(DEG_TO_RAD(fy), 0.0f, DEG_TO_RAD(fp));
		CMatrix mat(quaTemp);	
		vecPos = CVector3(0.0f, 0.0f, -1.0f);
		m_aoStars[i].m_vecPos = mat* vecPos;
		m_aoStars[i].m_vecPos *= 9000.0f;
		m_aoStars[i].m_iTexture = 0;
		
		fy = random01();
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
		//m_aoStars[i].m_vecColor.X() = RANDOM_FLOAT;
		//m_aoStars[i].m_vecColor.Y() = RANDOM_FLOAT;
		//m_aoStars[i].m_vecColor.Z() = RANDOM_FLOAT;
	}

        // Create sprite
        CMaterial oMaterial;
        oMaterial.m_oEmissive = CRGBAColour(1.0f, 1.0f, 1.0f,0);
        oMaterial.m_uiTexture = g_oTextureManager.load("an01.png");   
        m_oSprite = CSprite(oMaterial);
        m_oSprite.init();
        
        //m_auiTextures[1] = g_oTextureManager.load("an02.png");
        //m_auiTextures[2] = g_oTextureManager.load("an03.png");

}

void CStars::draw(CVector3 vecPos)
{
	glPushMatrix();
	glTranslatef(vecPos.X(), vecPos.Y(), vecPos.Z());

	for (int iCount = 0 ; iCount < m_iNumStars ; iCount++)
	{
		if (m_oFrustum.PointInFrustum(m_aoStars[iCount].m_vecPos))
		{
			// Set size
			m_oSprite.setSize(m_aoStars[iCount].m_fSize);
			// Set position
			m_oSprite.setTranslation(m_aoStars[iCount].m_vecPos);
			// Render
			m_oSprite.render();
		}
	}
	
	glPopMatrix();
}

