// 2DObject.h: interface for the C2DObject class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_2DOBJECT_H__90BFDDBC_B0A5_4AD3_8A38_13C4ECC07894__INCLUDED_)
#define AFX_2DOBJECT_H__90BFDDBC_B0A5_4AD3_8A38_13C4ECC07894__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "config.h"
#include <GL/gl.h>
#include "math/vector.h"

class C2DObject  
{
public:
	void setScreen(int iWidth, int iHeight);
	void setPosition(int iXPos, int iYPos);
   C2DObject();
   virtual ~C2DObject();
   void C2DObject::renderQuad(float fPosX, float fPosY, float fWidth, 
	   float fHeight, CVector2* vecTex);

private:
 
   int m_iXPos;
   int m_iYPos;

   static int m_iWidth;
   static int m_iHeight;
};

#endif // !defined(AFX_2DOBJECT_H__90BFDDBC_B0A5_4AD3_8A38_13C4ECC07894__INCLUDED_)
