// Ship.cpp: implementation of the CShip class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Ship.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShip::CShip(int num, float mass) : 
   CGameObject(num, mass),
   m_vecLastForce(0.0f,0.0f,0.0f),
   m_vecBrakePoint(0.0f,0.0f,0.0f),
   m_bStraffUp(false),
   m_bStraffDown(false),
   m_bStraffRight(false),
   m_bStraffLeft(false),
   m_vecCamView(0.0f,0.0f,0.0f),
   m_fCamPitch(0.0f),
   m_fCamYaw(0.0f),
   m_fThrust(0.0f),
   m_poTrails(NULL),
   m_poWeapon(NULL),
   m_poBrake(NULL),
   m_iFlightMode(1),
   m_bWeaponFire(false),
   m_bBraking(false)
{
   //initialise data
   m_quaCamOrientation.loadIdentity();
   m_matCamRotation.loadIdentity();

   m_poBrake = new CBrake(100,CVector3(0.0f, 0.0f, 0.0f));
}

CShip::~CShip()
{
}

//load model, trail texture and brake texture
void CShip::load()
{
   for (int i=0; i<m_iNumTrails; i++)
      m_poTrails[i].init();
   m_poBrake->init();
   m_poWeapon->init();
}

void CShip::drawBlended() {

   // Draw trail
   if (m_fThrust != 0.0f) {
      for (int i=0; i<m_iNumTrails; i++) {
         m_poTrails[i].render();
      }
   }

   // Draw weapons fire
   m_poWeapon->render();

   // Draw brake exhaust
   m_poBrake->render();

}

//This function calculates the force acting on the ship
void CShip::solve()
{
	CVector3 vecForce, vecDragForce, vecBrakeForce;

	if (m_iFlightMode == 1)
	{
		//Normal flight, forces are thrust, drag and braking (if applied)
		vecForce = (m_vecHeading - m_ppMasses[0]->m_vecPos) * m_fThrust;
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

		m_fThrust = 0.0f;
	}

	//Straff mode. The length of the last force is applied in the
	//direction of the joystick (amended, doubled the last force to 
	//make the effect more noticable)
	if (m_iFlightMode == 3)
	{
		m_fThrust = 0.0f;
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

	CGameObject::simulate (fDT);

	//get the amount of movement to calculate speed
	vecDistanceMoved = m_ppMasses[0]->m_vecPos - m_ppMasses[0]->m_vecOldPos;

	//update trail, weapons and heading
        for (int i=0; i<m_iNumTrails; i++) 
           m_poTrails[i].update(fDT, m_fThrust, m_ppMasses[0]->m_vecPos, m_avecTrailPoints[i], vecDistanceMoved, 
                                             m_vecUp - m_ppMasses[0]->m_vecPos, m_vecRight - m_ppMasses[0]->m_vecPos, 1.5f, 0.5f);
	vecGunHead = m_vecHeading - m_ppMasses[0]->m_vecPos;
	m_poWeapon->update(fDT, vecGunHead, m_avecWeaponPoints[0], m_fVel, m_bWeaponFire);
	m_poBrake->update(fDT, m_ppMasses[0]->m_vecPos, m_vecDirection, m_vecBrakePoint, m_bBraking);
}


void CShip::rotHeading(CMatrix mat)
{
   CGameObject::rotHeading(mat);
   m_avecWeaponPoints[0] = mat * CVector3( 0.0f,-0.7f,-7.3f) + m_ppMasses[0]->m_vecPos;
   for (int i=0; i<m_iNumTrails; i++)
      m_avecTrailPoints[i]  = mat * m_avecOrigTrailPoints[i] + m_ppMasses[0]->m_vecPos;
   m_vecBrakePoint       = mat * CVector3( 0.0f, 0.7f,-2.5f) + m_ppMasses[0]->m_vecPos;
   m_vecCamView         += m_ppMasses[0]->m_vecPos;
}


