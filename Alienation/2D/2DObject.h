// 2DObject.h: interface for the C2DObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_2DOBJECT_H__90BFDDBC_B0A5_4AD3_8A38_13C4ECC07894__INCLUDED_)
#define AFX_2DOBJECT_H__90BFDDBC_B0A5_4AD3_8A38_13C4ECC07894__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Math/Vector.h"
#include "3D/TextureManager.h"
#include "3D/Material.h"
#include "config.h"
#include <GL/gl.h>
#include <GL/glext.h>


class C2DObject  
{
public:
	void setActiveMaterial(CMaterial *oMaterial);
	void setActiveMaterial(CRGBAColour oDiffuse, CRGBAColour oAmbient, CRGBAColour oEmissive);
	void setActiveMaterial(CRGBAColour oDiffuse, CRGBAColour oAmbient, CRGBAColour oEmissive, unsigned int uiTexture);
	void setAltMaterial(CMaterial *oMaterial);
	void swapTextures();
	void swapMaterials();
   unsigned int getActiveTexture();
   void setActiveTexture(unsigned int uiTexture);
   unsigned int getAltTexture();
   void setAltTexture(unsigned int uiTexture);
   float getHeight();
   float getWidth();
   float getLeft();
   float getTop();
   bool mouseClickedInside(int iXPos, int iYPos);
   void setTexturePercentage(float fPercentage);
   void setPosition(float fXPos, float fYPos, float fWidth, float fHeight);
   C2DObject();
   virtual ~C2DObject();
   void init2D(float fXPos, float fYPos, float fWidth, float fHeight, const char *sFilename);
   void renderQuad();

private:
   NSDMath::CVector2 m_vecTex[4];
   unsigned m_uiActiveTexture;
   unsigned int m_uiAltTexture;
   CMaterial m_oActiveMaterial;
   CMaterial m_oAltMaterial;
   float m_fXPos;
   float m_fYPos;
   float m_fWidth;
   float m_fHeight;

};

#endif // !defined(AFX_2DOBJECT_H__90BFDDBC_B0A5_4AD3_8A38_13C4ECC07894__INCLUDED_)
