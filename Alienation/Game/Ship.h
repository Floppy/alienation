// Ship.h: interface for the CShip class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SDS_SHIP_H
#define SDS_SHIP_H

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Game/GameObject.h"
#include "Game/Weapon.h"
#include "Game/Brake.h"
#include "Game/Trail.h"

//OK the biggy. How this class eveolves is up for debate. My own view
//is that it should hold the data for every ship available in the game, 
//and a child/friend class should hold data for ships in sector/visible.
//However, there are many ways round this and it should develop in time.

//At the moment simply holds tha data for the static ship in the demo. 
class CShip : public CGameObject
{
 public:
   CShip(int num, float mass);
   virtual ~CShip();
   void load();
   virtual void drawBlended();
   virtual void solve();
   virtual void simulate(float dt);
   virtual void rotHeading(CMatrix m);

   
	CVector3		m_vecLastForce, m_vecBrakePoint;
	bool			m_bStraffUp, m_bStraffDown, m_bStraffRight, m_bStraffLeft;
	CVector3		m_vecCamView;
	CQuat			m_quaOrientation;
	CQuat			m_quaCamOrientation;
	float			m_fCamPitch, m_fCamYaw;
	float			m_fMaxPitchRate, m_fMaxYawRate, m_fMaxRollRate;
	float			m_fThrust;
	CMatrix		m_matCamRotation;
	CVector3		m_avecTrailPoints[4];
	CVector3		m_avecOrigTrailPoints[4];
	CVector3		m_avecWeaponPoints[4];
        int              m_iNumTrails;
	CTrail		*m_poTrails;
	CWeapon		*m_poWeapon;
	CBrake		*m_poBrake;
	int			m_iFlightMode;
	bool			m_bWeaponFire;
	bool			m_bBraking;

};

#endif // SDS_SHIP_H
