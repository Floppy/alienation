#ifndef AISHIP_H
#define AISHIP_H

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Game/Ship.h"

class CAIShip : public CShip  
{

public:

	CAIShip(int num, float mass, CVector3 position);
	virtual ~CAIShip();
	void load();
	void simulate(float fDT);
	void solve();

	float m_fXAngle;
	float m_fYAngle;


};

#endif // AISHIP_H
