// Ship.h: interface for the CShip class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHIP_H__8A1BAA92_3775_40B8_B34E_AFE14888CC50__INCLUDED_)
#define AFX_SHIP_H__8A1BAA92_3775_40B8_B34E_AFE14888CC50__INCLUDED_

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//#include "Physics/Physics1.h"
#include <stdio.h>
#include "Math/Vector.h"
#include "Math/Quat.h"
#include "Math/Matrix.h"
#include "Game/Weapon.h"
#include "Game/Brake.h"
#include "Game/Trail.h"
#include "3D/Model.h"
#include "3D/Frustum.h"
#include "3D/BoundingSphere.h"

class CShipData
{
public:
	CBoundingSphere m_oSphere;
	CShipData	*m_poTargetData;
	CMass			**m_poTargetMass;
	CModel	         m_oModel;
	CVector3		m_vecForce;
	CVector3		m_vecHeading, m_vecUp, m_vecRight, m_vecDirection;
	CVector3		m_vecLastForce, m_vecBrakePoint;
	bool			m_bStraffUp, m_bStraffDown, m_bStraffRight, m_bStraffLeft;
	CVector3		m_vecCamView;
	CQuat			m_quaOrientation;
	CQuat			m_quaCamOrientation;
	float			m_fPitch, m_fYaw, m_fRoll;
	float			m_fCamPitch, m_fCamYaw;
	float			m_fMaxPitchRate, m_fMaxYawRate, m_fMaxRollRate;
	float			m_fThrust;
	float			m_fPitchRate;
	float			m_fYawRate;
	float			m_fRollRate;
	CMatrix		m_matRotation;
	CMatrix		m_matCamRotation;
	float			m_fVel;
	CVector3		m_avecTrailPoints[4];
	CVector3		m_avecWeaponPoints[4];
        int              m_iNumTrails;
	CTrail		*m_poTrails;
	CWeapon		*m_poWeapon;
	CBrake		*m_poBrake;
	float			m_afq[16];
	float			m_fDrag;
	int			m_iFlightMode;
	bool			m_bWeaponFire;
	bool			m_bBraking;
};
//OK the biggy. How this class eveolves is up for debate. My own view
//is that it should hold the data for every ship available in the game, 
//and a child/friend class should hold data for ships in sector/visible.
//However, there are many ways round this and it should develop in time.

//At the moment simply holds tha data for the static ship in the demo. 
class CShip : public CSimulation  
{
 public:
   CShip(int num, float mass);
   virtual ~CShip();
   void loadShip();
   void rotate(int ship, float dt);
   void draw();
   void rotHeading(CMatrix m);
   virtual void solve();
   virtual void simulate(float dt);
   CShipData *m_poShips;
   CFrustum m_oFrustum;
};

#endif // !defined(AFX_SHIP_H__8A1BAA92_3775_40B8_B34E_AFE14888CC50__INCLUDED_)
