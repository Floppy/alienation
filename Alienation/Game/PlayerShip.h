// PlayerShip.h: interface for the CPlayerShip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERSHIP_H__037FA971_63AF_49C5_9C78_DCF151372718__INCLUDED_)
#define AFX_PLAYERSHIP_H__037FA971_63AF_49C5_9C78_DCF151372718__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "config.h"

#include "Game/Ship.h"
#include "3D/Model.h"
#include "2D/Hud.h"

//Player ship. A combination of ship and camera (pointless having them as 
//seperate classes as there can only be one of each). Derived from the CShip class
class CPlayerShip : public CShip  
{
public:
   	void drawHud();
	CPlayerShip();
	virtual ~CPlayerShip();
	void loadShip();
	virtual void simulate(float fDT);
	void draw();
	void rotateCam(float fDT);

	CModel m_oCockpitModel;
	bool  m_bInsideView;
	bool  m_bLeftLook, m_bRightLook, m_bUpLook, m_bBackLook;
        CHud *m_poHud;
};

#endif // !defined(AFX_PLAYERSHIP_H__037FA971_63AF_49C5_9C78_DCF151372718__INCLUDED_)
