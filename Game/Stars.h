// Stars.h: interface for the CStars class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STARS_H__32A2C3FB_4B7D_486A_9EF7_DFCF4869785B__INCLUDED_)
#define AFX_STARS_H__32A2C3FB_4B7D_486A_9EF7_DFCF4869785B__INCLUDED_

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdio.h>
#include "Math/Quat.h"
#include "Math/Matrix.h"
#include "Math/Vector.h"
#include "3D/Texture.h"
#include "3D/Frustum.h"
#include "3D/Sprite.h"

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
	unsigned int m_auiTextures[3];
	void initStars();
	void draw(CVector3 vecPos);
private:
        CSprite m_oSprite;
	CFrustum m_oFrustum;
};

#endif // !defined(AFX_STARS_H__32A2C3FB_4B7D_486A_9EF7_DFCF4869785B__INCLUDED_)
