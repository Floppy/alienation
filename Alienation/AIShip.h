// AIShip.h: interface for the CAIShip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AISHIP_H__F4D5F9B3_AF42_4BEC_B7F4_415475A9F316__INCLUDED_)
#define AFX_AISHIP_H__F4D5F9B3_AF42_4BEC_B7F4_415475A9F316__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Ship.h"

class CAIShip : public CShip  
{
public:
	CAIShip(int num, float mass);
	virtual ~CAIShip();
	void simulate(float fDT);
	void solve();
	CVector3 m_vecTarget;
	float m_fXAngle;
	float m_fYAngle;
	CVector3 m_vecTargetPos;
};

#endif // !defined(AFX_AISHIP_H__F4D5F9B3_AF42_4BEC_B7F4_415475A9F316__INCLUDED_)
