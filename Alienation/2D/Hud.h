// Hud.h: interface for the CHud class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HUD_H__C6F6120B_C8C6_4FCA_940B_676EE263ED19__INCLUDED_)
#define AFX_HUD_H__C6F6120B_C8C6_4FCA_940B_676EE263ED19__INCLUDED_

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "3D/Texture.h"
#include "GL/GLFont.h"
#include "Game/Ship.h"

class CHud  
{
public:
	void drawHoloTarget(CShipData *poTarget, CMass **m_poMass, CShip *poThisShip);
	void drawQuad(CVector3 *Verts, CVector2 *Tex);
	void draw2DQuad(float fPosX, float fPosY, float fWidth, float fHeight, CVector2 *Tex);
	void init();
	void draw(float fSpeed, float fMaxSpeed, float fThrust, float fMaxThrust);
	CHud();
	virtual ~CHud();

	CTexture *m_poTexture;
	CGLFont  *m_poFont;
        unsigned long m_iLastTime;

};

#endif // !defined(AFX_HUD_H__C6F6120B_C8C6_4FCA_940B_676EE263ED19__INCLUDED_)
