// Ship.cpp: implementation of the CShip class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Ship.h"
#include "Game/WeaponFactory.h"
#include "IO/3ds.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShip::CShip(float mass) : 
   CGameObject(1, mass),
   m_vecLastForce(0.0f,0.0f,0.0f),
   m_bStraffUp(false),
   m_bStraffDown(false),
   m_bStraffRight(false),
   m_bStraffLeft(false),
   m_vecCamView(0.0f,0.0f,0.0f),
   m_fCamPitch(0.0f),
   m_fCamYaw(0.0f),
   m_fMaxPitchRate(0.0f),
   m_fMaxYawRate(0.0f),
   m_fMaxRollRate(0.0f),
   m_avecEnginePoints(NULL),
   m_avecOrigEnginePoints(NULL),
   m_avecWeaponPoints(NULL),
   m_avecOrigWeaponPoints(NULL),
   m_avecBrakePoints(NULL),
   m_avecOrigBrakePoints(NULL),
   m_iNumEngines(0),
   m_iNumWeapons(0),
   m_iNumBrakes(0),
   m_ppEngines(NULL),
   m_ppWeapons(NULL),
   m_ppBrakes(NULL),
   m_iFlightMode(1),
   m_bWeaponFire(false),
   m_bBraking(false)
{
   m_fDrag = 25.0f;   

   setPosition(CVector3(0,0,0));
   m_ppMasses[0]->m_vecVel = CVector3(0.0f, 0.0f, 0.0f);

   //initialise data
   m_quaCamOrientation.loadIdentity();
   m_matCamRotation.loadIdentity();

}

CShip::~CShip()
{
   int i;
   delete [] m_avecBrakePoints;
   delete [] m_avecOrigBrakePoints;
   for (i=0; i<m_iNumBrakes; i++) 
      delete m_ppBrakes[i];
   delete [] m_ppBrakes;

   delete [] m_avecWeaponPoints;
   delete [] m_avecOrigWeaponPoints;
   for (i=0; i<m_iNumWeapons; i++) 
      delete m_ppWeapons[i];
   delete [] m_ppWeapons;

   delete [] m_avecEnginePoints;
   delete [] m_avecOrigEnginePoints;
   for (i=0; i<m_iNumEngines; i++) 
      delete m_ppEngines[i];
   delete [] m_ppEngines;

   for (vector<CShield*>::iterator it = m_lShields.begin(); it != m_lShields.end(); it++) {
      delete *it;
   }

}

//load model
void CShip::load(const char* strShipModel, const char* strCockpitModel)
{

   NSDIO::CLoad3DS oLoad3ds;
   if (oLoad3ds.import3DS(&(m_oModel), strShipModel)) {
      m_oModel.init();
   }
   if (strCockpitModel && oLoad3ds.import3DS(&m_oCockpitModel, strCockpitModel)) {
      // Prepare
      m_oCockpitModel.init();
   }
}

void CShip::drawBlended() {
   int i;

   // Draw engines
   for (i=0; i<m_iNumEngines; i++)
      m_ppEngines[i]->drawBlended();
   
   // Draw weapons fire
   for (i=0; i<m_iNumWeapons; i++)
      m_ppWeapons[i]->render();
   
   // Draw brake exhausts
   for (i=0; i<m_iNumBrakes; i++)
      m_ppBrakes[i]->render();
   
}

//This function calculates the force acting on the ship
void CShip::solve()
{
        CVector3 vecForce, vecDragForce, vecBrakeForce;

	if (m_iFlightMode == 1)
	{
           // Add up engine thrusts
           float fThrust(0);
           for (int i=0; i<m_iNumEngines; i++)
              fThrust += m_ppEngines[i]->getThrust();


		//Normal flight, forces are thrust, drag and braking (if applied)
		vecForce = (m_vecHeading - m_ppMasses[0]->m_vecPos) * fThrust;
		vecDragForce = (m_vecDirection * -1 ) * (m_fDrag * m_fVel);
		if (m_bBraking && m_fVel != 0.0f)
		{
			vecBrakeForce = (m_vecDirection * -1 ) * 3000;
		}
		else
		{
			vecBrakeForce = CVector3(0.0f, 0.0f, 0.0f);
		}
		m_vecForce = vecForce + vecDragForce;
		m_vecForce += vecBrakeForce;
		//The last force applied is stored in case the user switches to straff mode
		m_vecLastForce = m_vecForce;

	}

	//Turret mode, absolutely no forces applied, ship just drifts
	if (m_iFlightMode == 2)
	{
		m_vecForce = CVector3(0.0f, 0.0f, 0.0f);

		setThrust(0.0f);
	}

	//Straff mode. The length of the last force is applied in the
	//direction of the joystick (amended, doubled the last force to 
	//make the effect more noticable)
	if (m_iFlightMode == 3)
	{
		setThrust(0.0f);
		CVector3 vecTemp = CVector3(0.0f, 0.0f, 0.0f);
		float fLen = m_vecLastForce.length() * 2.0f;

		if (m_bStraffDown)
		{
			vecTemp += (m_vecUp - m_ppMasses[0]->m_vecPos) * - fLen;
		}
		if (m_bStraffUp)
		{
			vecTemp += (m_vecUp - m_ppMasses[0]->m_vecPos) * fLen;
		}
		if (m_bStraffRight)
		{
			vecTemp += (m_vecRight - m_ppMasses[0]->m_vecPos) * fLen;
		}
		if (m_bStraffLeft)
		{
			vecTemp += (m_vecRight - m_ppMasses[0]->m_vecPos) * -fLen;
		}
		m_vecForce = vecTemp;
	}
	//apply the force to the ship
	m_ppMasses[0]->applyForce(m_vecForce);
}

//Applies the time based update
void CShip::simulate(float fDT)
{
	CVector3	vecDistanceMoved, vecGunHead;
        int i;
	CGameObject::simulate (fDT);
        
	//get the amount of movement to calculate speed
	vecDistanceMoved = m_ppMasses[0]->m_vecPos - m_ppMasses[0]->m_vecOldPos;
        
	//update engine, weapons and heading
        for (i=0; i<m_iNumEngines; i++) 
           m_ppEngines[i]->update(fDT, m_ppMasses[0]->m_vecPos, m_avecEnginePoints[i], vecDistanceMoved, 
                                m_vecUp - m_ppMasses[0]->m_vecPos, m_vecRight - m_ppMasses[0]->m_vecPos);
	vecGunHead = m_vecHeading - m_ppMasses[0]->m_vecPos;
        for (i=0; i<m_iNumWeapons; i++)
           m_ppWeapons[i]->update(fDT, vecGunHead, m_avecWeaponPoints[i], m_fVel, m_bWeaponFire);
        // Update brakes
        for (i=0; i<m_iNumBrakes; i++) 
           m_ppBrakes[i]->update(fDT, m_ppMasses[0]->m_vecPos, m_vecDirection, m_avecBrakePoints[i], m_bBraking);
}


void CShip::rotHeading(CMatrix mat)
{
   CGameObject::rotHeading(mat);
   int i;
   for (i=0; i<m_iNumWeapons; i++)
      m_avecWeaponPoints[i] = mat * m_avecOrigWeaponPoints[i] + m_ppMasses[0]->m_vecPos;
   for (i=0; i<m_iNumEngines; i++)
      m_avecEnginePoints[i] = mat * m_avecOrigEnginePoints[i] + m_ppMasses[0]->m_vecPos;
   for (i=0; i<m_iNumBrakes; i++)
      m_avecBrakePoints[i]  = mat * m_avecOrigBrakePoints[i]  + m_ppMasses[0]->m_vecPos;
   m_vecCamView         += m_ppMasses[0]->m_vecPos;
}


void CShip::setPosition(const CVector3& pos)
{
   m_ppMasses[0]->m_vecPos = pos;
   m_vecHeading = m_ppMasses[0]->m_vecPos + CVector3(0.0f, 0.0f, -1.0f);
   m_vecUp = m_ppMasses[0]->m_vecPos + CVector3(0.0f, 1.0f, 0.0f);
   m_vecRight = m_ppMasses[0]->m_vecPos + CVector3(1.0f, 0.0f, 0.0f);
   m_vecDirection = m_vecHeading;   
}

void CShip::setPerformance(float fPitchRate, float fYawRate, float fRollRate) {
   m_fMaxPitchRate = fPitchRate;
   m_fMaxYawRate = fYawRate;
   m_fMaxRollRate = fRollRate;
}

void CShip::setWeapons(unsigned int iNumWeapons, const CVector3* pWeapons, const char* strWeapon) {
   // Store weapon locations
   m_ppWeapons = new CWeapon*[iNumWeapons];
   m_avecWeaponPoints = new CVector3[iNumWeapons];
   m_avecOrigWeaponPoints = new CVector3[iNumWeapons];
   // Copy data and setup
   m_iNumWeapons = iNumWeapons;
   for (int i=0; i<m_iNumWeapons; i++) {
      m_avecWeaponPoints[i] = m_avecOrigWeaponPoints[i] = pWeapons[i];
      m_ppWeapons[i] = CWeaponFactory::load(strWeapon);
      m_ppWeapons[i]->init();
   }
}

void CShip::setEngines(unsigned int iNumEngines, const CVector3* pEngines, const char* strEngine)
{
   // Allocate memory
   m_ppEngines = new CEngine*[iNumEngines];
   m_avecEnginePoints = new CVector3[iNumEngines];
   m_avecOrigEnginePoints = new CVector3[iNumEngines];
   // Copy data and setup
   m_iNumEngines = iNumEngines;
   for (int i=0; i<m_iNumEngines; i++) {
      m_avecEnginePoints[i] = m_avecOrigEnginePoints[i] = pEngines[i];
      m_ppEngines[i] = CEngine::load(strEngine);
   }
}

void CShip::setBrakes(unsigned int iNumBrakes, const CVector3* pBrakes)
{
   // Store thruster locations
   m_ppBrakes = new CBrake*[iNumBrakes];
   m_avecBrakePoints = new CVector3[iNumBrakes];
   m_avecOrigBrakePoints = new CVector3[iNumBrakes];
   // Copy data and setup
   m_iNumBrakes = iNumBrakes;
   for (int i=0; i<m_iNumBrakes; i++) {
      m_avecBrakePoints[i] = m_avecOrigBrakePoints[i] = pBrakes[i];
      m_ppBrakes[i] = new CBrake(100,m_avecBrakePoints[i]);
      m_ppBrakes[i]->init();
   }
}

void CShip::setThrust(float fThrust) {
   // Clip to 0..1
   if (fThrust > 1.0f)
      fThrust = 1.0f;
   else if (fThrust < 0.0f)
      fThrust = 0.0f;
   // Set thrust data
   for (int i=0; i<m_iNumEngines; i++) {
      m_ppEngines[i]->setThrust(fThrust);
   }
}
