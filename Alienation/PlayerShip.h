// PlayerShip.h: interface for the CPlayerShip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYERSHIP_H__037FA971_63AF_49C5_9C78_DCF151372718__INCLUDED_)
#define AFX_PLAYERSHIP_H__037FA971_63AF_49C5_9C78_DCF151372718__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ship.h"

#define RANDOM_FLOAT ((float)(rand()%1000)/1000.0f)     // Returns a random value between 0.0f and 1.0f
#define piover180 	(0.0174532925f)

//Player ship. A combination of ship and camera (pointless having them as 
//seperate classes as there can only be one of each). Derived from the CShip class
class CPlayerShip : public CShip  
{
public:
	CPlayerShip();
	virtual ~CPlayerShip();
	void loadShip();
	virtual void simulate(float fDT);
	void draw();
	void rotateCam(float fDT);

	C3dsLoader m_oCockpitModel;
	bool	m_bInsideView;
	bool  m_bLeftLook, m_bRightLook, m_bUpLook, m_bBackLook;
};

#endif // !defined(AFX_PLAYERSHIP_H__037FA971_63AF_49C5_9C78_DCF151372718__INCLUDED_)
