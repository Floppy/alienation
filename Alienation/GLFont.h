// GLFont.h: interface for the CGLFont class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GLFONT_H__1F582CF0_7FA7_4B78_9D84_724C2654D02F__INCLUDED_)
#define AFX_GLFONT_H__1F582CF0_7FA7_4B78_9D84_724C2654D02F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdio.h>
#include <windows.h>
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>
#include "texture.h"
#include "vector.h"
#include "matrix.h"


//The infamous font class. Saw many that did a similar trick, but where far more complex. So wrote this one :)
//I think this one will be expanded fairly simply
class CGLFont  
{
public:
	void print(char * str, CVector3 vecPos, float fSize);
	void load();
	CGLFont();
	virtual ~CGLFont();
	CTexture *m_poTexture;
};

#endif // !defined(AFX_GLFONT_H__1F582CF0_7FA7_4B78_9D84_724C2654D02F__INCLUDED_)
