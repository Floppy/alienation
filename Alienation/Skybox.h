// Skybox.h: interface for the CSkybox class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SKYBOX_H__26E22004_D75B_4D10_808A_0462FBA1B220__INCLUDED_)
#define AFX_SKYBOX_H__26E22004_D75B_4D10_808A_0462FBA1B220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3dsLoader.h"
#include "Vertices.h"
#include <gl\gl.h>			// Header File For The OpenGL32 Library
#include <gl\glu.h>			// Header File For The GLu32 Library
#include <gl\glaux.h>		// Header File For The Glaux Library

class CSkybox  
{
public:
	C3dsLoader model;
	unsigned int texture[6];
	unsigned int list;
	
	CSkybox();
	virtual ~CSkybox();
	void DrawSB(CVector3 pos);
	void initSB();
	AUX_RGBImageRec * LoadBMP(char *Filename);
	bool LoadGLTextures();
};

#endif // !defined(AFX_SKYBOX_H__26E22004_D75B_4D10_808A_0462FBA1B220__INCLUDED_)
