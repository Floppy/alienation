// Ship.h: interface for the CShip class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SDS_SHIP_H
#define SDS_SHIP_H

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CShip;

#include "Game/GameObject.h"
#include "Game/Weapon.h"
#include "Game/Brake.h"
#include "Equipment/Engine.h"
#include "Equipment/Shield.h"
#include "Equipment/SpeedIndicator.h"
#include "Equipment/ThrustInformation.h"
#include "Equipment/TargetingComputer.h"

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

   virtual void setPerformance(float fPitchRate, float fYawRate, float fRollRate);
   
   void setWeapons(unsigned int iNumWeapons, const CVector3* pWeapons, const char* strWeapon);

   void setEngines(unsigned int iNumEngines, const CVector3* pEngines, const char* strEngine);

   void setBrakes(unsigned int iNumBrakes, const CVector3* pBrakes);

   void setThrust(float fThrust);

	CVector3		m_vecLastForce;
	bool			m_bStraffUp, m_bStraffDown, m_bStraffRight, m_bStraffLeft;
	CVector3		m_vecCamView;
	CQuat			m_quaCamOrientation;
	float			m_fCamPitch, m_fCamYaw;
	float			m_fMaxPitchRate, m_fMaxYawRate, m_fMaxRollRate;
	CMatrix		m_matCamRotation;
	CVector3*		m_avecEnginePoints;
	CVector3*		m_avecOrigEnginePoints;
	CVector3*		m_avecWeaponPoints;
	CVector3*		m_avecOrigWeaponPoints;
	CVector3*		m_avecBrakePoints;
	CVector3*		m_avecOrigBrakePoints;
        int              m_iNumEngines;
        int              m_iNumWeapons;
        int              m_iNumBrakes;
	CEngine**	 m_ppEngines;
	CWeapon**        m_ppWeapons;
	CBrake**	 m_ppBrakes;
	int			m_iFlightMode;
	bool			m_bWeaponFire;
	bool			m_bBraking;
	CModel m_oCockpitModel;

        vector<CShield*> m_lShields;
        CSpeedIndicator * m_poSpeedIndicator;        
        CThrustIndicator * m_poThrustIndicator;        
        CTargetingComputer * m_poTargetingComputer;

};

#endif // SDS_SHIP_H
