// Radar.h: interface for the CRadar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADAR_H__B2305CC7_9100_4FE5_911F_F1536522D58C__INCLUDED_)
#define AFX_RADAR_H__B2305CC7_9100_4FE5_911F_F1536522D58C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "3D/Light.h"
#include "Equipment/Equipment.h"
#include "Math/Vector.h"
#include "3D/Texture.h"
#include <GL/glu.h>
#include <vector>
using namespace std;




class CRadar : 
	public CEquipment
{
public:
	void clearTargetList();
	void setRange(unsigned int uiRange);
	unsigned int m_uiRange;
	void setTarget(int iTargetID);
	void render();
	void renderOffScreen(CVector3 vecShipPos);
	void init();
	void addTarget(int iObjectID, int iTargetType, CVector3 vecPos);
	CRadar();
	virtual ~CRadar();
private:
	struct sTarget
	{
		int iObjectID;
		int iTargetType;
		CVector3 vecPos;
	};
	vector <sTarget> m_arrTarget;
	GLUquadricObj *m_poQuadric;
   /**
    * Light for radar display
    */
   CLight *m_oLight;
	CMaterial m_oOffScreenMaterial;
	unsigned int m_uiOffScreenTexture;
	int m_iTargetID;
	CMaterial m_oOuterSphereTexture;
	CMaterial m_oMidSphereTexture;
	CMaterial m_oInnerSphereTexture;
};

#endif // !defined(AFX_RADAR_H__B2305CC7_9100_4FE5_911F_F1536522D58C__INCLUDED_)
