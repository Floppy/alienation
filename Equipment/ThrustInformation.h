// ThrustInformation.h: interface for the CThrustInformation class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_THRUSTINFORMATION_H__307BE012_ED12_4583_AD84_4A4EE597BEB5__INCLUDED_)
#define AFX_THRUSTINFORMATION_H__307BE012_ED12_4583_AD84_4A4EE597BEB5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equipment/HudInformation.h"

class CThrustIndicator : public CHudInformation  
{
public:
	CThrustIndicator();
	virtual ~CThrustIndicator();

        void init2D(float fXPos, float fYPos, float fWidth, float fHeight, const char *sFilename);
        void renderQuad();
        void setActiveMaterial(CRGBAColour oDiffuse, CRGBAColour oAmbient, CRGBAColour oEmissive);

private:
        C2DObject m_oScale;
};

#endif // !defined(AFX_THRUSTINFORMATION_H__307BE012_ED12_4583_AD84_4A4EE597BEB5__INCLUDED_)
