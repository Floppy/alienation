// Stars.h: interface for the CStars class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STARS_H__32A2C3FB_4B7D_486A_9EF7_DFCF4869785B__INCLUDED_)
#define AFX_STARS_H__32A2C3FB_4B7D_486A_9EF7_DFCF4869785B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdio.h>
#include "quat.h"
#include "matrix.h"
#include "vector.h"
#include "Texture.h"

#define RANDOM_FLOAT ((float)(rand()%1000)/1000.0f)     // Returns a random value between 0.0f and 1.0f
#define piover180 	(0.0174532925f)

class CStar
{
public:
	int m_iTexture;
	float m_fSize;
	CVector3 m_vecColor;
	CVector3 m_vecPos;
};

class CStars  
{
public:
	CStars();
	CStar m_aoStars[500];
	virtual ~CStars();
	int m_iNumStars;
	CTexture *m_poTexture;
	void initStars();
	void draw(CVector3 vecPos);
};

#endif // !defined(AFX_STARS_H__32A2C3FB_4B7D_486A_9EF7_DFCF4869785B__INCLUDED_)
