// 2DObject.cpp: implementation of the C2DObject class.
//
//////////////////////////////////////////////////////////////////////
#include "2D/2DObject.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

C2DObject::C2DObject()
{

}

C2DObject::~C2DObject()
{

}

void C2DObject::renderQuad()
{
//   g_oTextureManager.render(m_uiActiveTexture);
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glMatrixMode(GL_PROJECTION); 
   glPushMatrix(); 
   glLoadIdentity(); 
   glEnable(GL_TEXTURE_2D);
   glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

   m_oActiveMaterial.render();

   glBegin(GL_QUADS);

	  glTexCoord2fv(m_vecTex[0].glVector());
	  glVertex2f(m_fXPos, m_fYPos);
	  glTexCoord2fv(m_vecTex[1].glVector());
	  glVertex2f(m_fXPos + m_fWidth, m_fYPos);
	  glTexCoord2fv(m_vecTex[2].glVector());
	  glVertex2f(m_fXPos + m_fWidth, m_fYPos + m_fHeight);
	  glTexCoord2fv(m_vecTex[3].glVector());
	  glVertex2f(m_fXPos, m_fYPos + m_fHeight);

   glEnd();
   glPopMatrix();
   glMatrixMode(GL_MODELVIEW);
   glPopMatrix();
}

void C2DObject::setPosition(float fXPos, float fYPos, float fWidth, float fHeight)
{
   m_fXPos = fXPos;
   m_fYPos = fYPos;
   m_fWidth = fWidth;
   m_fHeight = fHeight;
}

void C2DObject::init2D(float fXPos, float fYPos, float fWidth, float fHeight, char * strFilename)
{
   CMaterial oMaterial; 
   m_fXPos = fXPos;
   m_fYPos = fYPos;
   m_fWidth = fWidth;
   m_fHeight = fHeight;

   m_vecTex[0] = NSDMath::CVector2(0.0f, 1.0f);

   m_vecTex[1] = NSDMath::CVector2(1.0f, 1.0f);

   m_vecTex[2] = NSDMath::CVector2(1.0f, 0.0f);

   m_vecTex[3] = NSDMath::CVector2(0.0f, 0.0f);

//   m_oActiveMaterial = CMaterial();
   m_oActiveMaterial.m_uiTexture = g_oTextureManager.load(strFilename);
   m_oActiveMaterial.init();

   setTexturePercentage(100.00f);

}

void C2DObject::setTexturePercentage(float fPercentage)
{
   m_vecTex[0] = NSDMath::CVector2(0.0f, 1.0f);

   m_vecTex[1] = NSDMath::CVector2(1.0f * (fPercentage / 100.0f), 1.0f);

   m_vecTex[2] = NSDMath::CVector2(1.0f * (fPercentage / 100.0f), 0.0f);

   m_vecTex[3] = NSDMath::CVector2(0.0f, 0.0f);
  
}

bool C2DObject::mouseClickedInside(int iXPos, int iYPos)
{
	if ((iXPos >= m_fXPos && iXPos <= m_fXPos + m_fWidth) &&
		(iYPos >= m_fYPos && iYPos <= m_fYPos + m_fHeight))
	{
		return true;
	} 
	else
	{
		return false;
	}
}

float C2DObject::getTop()
{
   return m_fYPos;
}

float C2DObject::getLeft()
{
   return m_fXPos;
}

float C2DObject::getWidth()
{
   return m_fWidth;
}

float C2DObject::getHeight()
{
   return m_fHeight;
}

void C2DObject::setAltTexture(unsigned int uiTexture)
{
   m_uiAltTexture = uiTexture;
}

unsigned int C2DObject::getAltTexture()
{
   return m_uiAltTexture;
}

void C2DObject::setActiveTexture(unsigned int uiTexture)
{
   m_uiActiveTexture = uiTexture;
}

unsigned int C2DObject::getActiveTexture()
{
   return m_uiActiveTexture;
}



void C2DObject::swapTextures()
{
   unsigned int uiTemp;
   uiTemp = m_uiActiveTexture;
   m_uiActiveTexture = m_uiAltTexture;
   m_uiAltTexture = uiTemp;
}



void C2DObject::setActiveMaterial(CRGBAColour oDiffuse, CRGBAColour oAmbient, CRGBAColour oEmissive)
{
   m_oActiveMaterial.init();
   m_oActiveMaterial.m_oDiffuse = oDiffuse;
   m_oActiveMaterial.m_oAmbient = oAmbient;
   m_oActiveMaterial.m_oEmissive = oEmissive;
}
