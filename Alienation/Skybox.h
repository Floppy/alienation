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
#include <GL/gl.h>			// Header File For The OpenGL32 Library
#include <GL/glu.h>			// Header File For The GLu32 Library

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
	bool LoadGLTextures();
};

#endif // !defined(AFX_SKYBOX_H__26E22004_D75B_4D10_808A_0462FBA1B220__INCLUDED_)
