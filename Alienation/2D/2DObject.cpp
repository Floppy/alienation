// 2DObject.cpp: implementation of the C2DObject class.
//
//////////////////////////////////////////////////////////////////////
#include "2D/2DObject.h"
#include "GL/Extensions.h"

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
   glMatrixMode(GL_MODELVIEW);
   glPushMatrix();
   glLoadIdentity();
   glMatrixMode(GL_PROJECTION); 
   glPushMatrix(); 
   glLoadIdentity(); 
   glEnable(GL_TEXTURE_2D);
   glOrtho(0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f);

   m_oActiveMaterial.render();
	m_oActiveMaterial.disableDot3();

   glBegin(GL_QUADS);

	  glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_vecTex[0].X(), m_vecTex[0].Y());
	  glMultiTexCoord2fARB(GL_TEXTURE1_ARB, m_vecTex[0].X(), m_vecTex[0].Y());
	  glVertex2f(m_fXPos, m_fYPos + m_fHeight);
	  glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_vecTex[1].X(), m_vecTex[1].Y());
	  glMultiTexCoord2fARB(GL_TEXTURE1_ARB, m_vecTex[1].X(), m_vecTex[1].Y());
	  glVertex2f(m_fXPos + m_fWidth, m_fYPos + m_fHeight);
	  glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_vecTex[2].X(), m_vecTex[2].Y());
	  glMultiTexCoord2fARB(GL_TEXTURE1_ARB, m_vecTex[2].X(), m_vecTex[2].Y());
	  glVertex2f(m_fXPos + m_fWidth, m_fYPos);
	  glMultiTexCoord2fARB(GL_TEXTURE0_ARB, m_vecTex[3].X(), m_vecTex[3].Y());
	  glMultiTexCoord2fARB(GL_TEXTURE1_ARB, m_vecTex[3].X(), m_vecTex[3].Y());
	  glVertex2f(m_fXPos, m_fYPos);

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

void C2DObject::init2D(float fXPos, float fYPos, float fWidth, float fHeight, const char * strFilename)
{
   CMaterial oMaterial; 
   m_fXPos = fXPos;
   m_fYPos = fYPos;
   m_fWidth = fWidth;
   m_fHeight = fHeight;
	char strNullString[1] = "";

   m_vecTex[0] = NSDMath::CVector2(0.0f, 1.0f);

   m_vecTex[1] = NSDMath::CVector2(1.0f, 1.0f);

   m_vecTex[2] = NSDMath::CVector2(1.0f, 0.0f);

   m_vecTex[3] = NSDMath::CVector2(0.0f, 0.0f);

	int iFileExists = strcmp(strFilename, strNullString);
	if ( iFileExists )
	{
	   m_oActiveMaterial.m_uiTexture = g_oTextureManager.load(strFilename);
		m_oActiveMaterial.init();
	}

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
   return m_oActiveMaterial.m_uiTexture;
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

void C2DObject::setActiveMaterial(CRGBAColour oDiffuse, CRGBAColour oAmbient, CRGBAColour oEmissive, unsigned int uiTexture)
{
   m_oActiveMaterial.m_oDiffuse = oDiffuse;
   m_oActiveMaterial.m_oAmbient = oAmbient;
   m_oActiveMaterial.m_oEmissive = oEmissive;
	m_oActiveMaterial.m_uiTexture = uiTexture;
   m_oActiveMaterial.init();
}

void C2DObject::setActiveMaterial(CMaterial *oMaterial)
{
   m_oActiveMaterial.m_oDiffuse = oMaterial->m_oDiffuse;
   m_oActiveMaterial.m_oAmbient = oMaterial->m_oAmbient;
   m_oActiveMaterial.m_oEmissive = oMaterial->m_oEmissive;
	m_oActiveMaterial.m_uiTexture = oMaterial->m_uiTexture;
//   m_oActiveMaterial.init();
}

void C2DObject::setAltMaterial(CMaterial *oMaterial)
{
   m_oAltMaterial.m_oDiffuse = oMaterial->m_oDiffuse;
   m_oAltMaterial.m_oAmbient = oMaterial->m_oAmbient;
   m_oAltMaterial.m_oEmissive = oMaterial->m_oEmissive;
	m_oAltMaterial.m_uiTexture = oMaterial->m_uiTexture;
}
