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

	CAIShip(int num, float mass);
	virtual ~CAIShip();
	void load();
	void simulate(float fDT);
	void solve();
	CVector3 m_vecTarget;
	float m_fXAngle;
	float m_fYAngle;
	CVector3 m_vecTargetPos;
	float m_fTargetSpeed;
	CVector3 m_vecTargetDirection;



};

#endif // AISHIP_H
