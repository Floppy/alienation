// GLFont.h: interface for the CGLFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLFONT_H__1F582CF0_7FA7_4B78_9D84_724C2654D02F__INCLUDED_)
#define AFX_GLFONT_H__1F582CF0_7FA7_4B78_9D84_724C2654D02F__INCLUDED_

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdio.h>
#include "3D/Texture.h"
#include "Math/Vector.h"
#include "Math/Matrix.h"


//The infamous font class. Saw many that did a similar trick, but where far more complex. So wrote this one :)
//I think this one will be expanded fairly simply
class CGLFont  
{
public:
	int getID();
	void setID(int iID);
	void print(char *str, NSDMath::CVector3 vecPos, float fSize);
	void print(char *str, NSDMath::CVector2 vecPos, float fSize, NSDMath::CVector3 vecColour);
	void load();
	CGLFont();
	virtual ~CGLFont();
private:
	int m_iID;
	unsigned int m_uiTexture;
};

#endif // !defined(AFX_GLFONT_H__1F582CF0_7FA7_4B78_9D84_724C2654D02F__INCLUDED_)
