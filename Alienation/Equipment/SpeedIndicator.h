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

        void init2D(float fXPos, float fYPos, float fWidth, float fHeight, const char *sFilename);
        void renderQuad();
	void setActiveMaterial(CRGBAColour oDiffuse, CRGBAColour oAmbient, CRGBAColour oEmissive);

private:
	float m_fSpeed;
        C2DObject m_oScale;

};

#endif // !defined(AFX_SPEEDINDICATOR_H__23D2CC30_9075_477C_ABC2_01B943596FED__INCLUDED_)
