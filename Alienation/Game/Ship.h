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
   CShip(float mass);
   virtual ~CShip();

   virtual void load(const char* strShipModel, const char* strCockpitModel = NULL);

   virtual void drawBlended();
   virtual void solve();
   virtual void simulate(float dt);
   virtual void rotHeading(CMatrix m);

   virtual void setPosition(const CVector3& pos);

   virtual void setPerformance(float fPitchRate, float fYawRate, float fRollRate, float fThrust);
   
   void setWeapons(unsigned int iNumWeapons, const CVector3* pWeapons, const char* strWeapon);

   void setTrails(unsigned int iNumTrails, const CVector3* pTrails);

   void setBrakes(unsigned int iNumBrakes, const CVector3* pBrakes);

	CVector3		m_vecLastForce;
	bool			m_bStraffUp, m_bStraffDown, m_bStraffRight, m_bStraffLeft;
	CVector3		m_vecCamView;
	CQuat			m_quaCamOrientation;
	float			m_fCamPitch, m_fCamYaw;
	float			m_fMaxPitchRate, m_fMaxYawRate, m_fMaxRollRate;
	float			m_fThrust;
	CMatrix		m_matCamRotation;
	CVector3*		m_avecTrailPoints;
	CVector3*		m_avecOrigTrailPoints;
	CVector3*		m_avecWeaponPoints;
	CVector3*		m_avecOrigWeaponPoints;
	CVector3*		m_avecBrakePoints;
	CVector3*		m_avecOrigBrakePoints;
        int              m_iNumTrails;
        int              m_iNumWeapons;
        int              m_iNumBrakes;
	CTrail		*m_poTrails;
	CWeapon**        m_ppWeapons;
	CBrake**	 m_ppBrakes;
	int			m_iFlightMode;
	bool			m_bWeaponFire;
	bool			m_bBraking;
	CModel m_oCockpitModel;

};

#endif // SDS_SHIP_H
