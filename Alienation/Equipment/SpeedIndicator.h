// SpeedIndicator.h: interface for the CSpeedIndicator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPEEDINDICATOR_H__23D2CC30_9075_477C_ABC2_01B943596FED__INCLUDED_)
#define AFX_SPEEDINDICATOR_H__23D2CC30_9075_477C_ABC2_01B943596FED__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equipment/HudInformation.h"

class CSpeedIndicator : public CHudInformation  
{
public:
	float getSpeed();
	void setSpeed(float fSpeed);
	CSpeedIndicator();
	virtual ~CSpeedIndicator();
	void operator = (CSpeedIndicator * poSpeed);

private:
	float m_fSpeed;
};

#endif // !defined(AFX_SPEEDINDICATOR_H__23D2CC30_9075_477C_ABC2_01B943596FED__INCLUDED_)
