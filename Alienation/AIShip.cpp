// AIShip.cpp: implementation of the CAIShip class.
//
//////////////////////////////////////////////////////////////////////

#include "AIShip.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAIShip::CAIShip(int num, float mass)  : CShip(1, 5000.0f)
{
	m_poShips = new CShipData[1];
	m_ppMasses[0]->m_vecPos = CVector3(0.0f, -5.0f, -20.0f);
	m_poShips[0].m_vecLastForce = CVector3(0.0f, 0.0f, 0.0f);
	m_poShips[0].m_bStraffUp = m_poShips[0].m_bStraffDown = m_poShips[0].m_bStraffLeft = m_poShips[0].m_bStraffRight = false;
	m_poShips[0].m_avecTrailPoints[0] = CVector3(0.0f, 0.0f, 7.0f);
	m_poShips[0].m_vecHeading = CVector3(0.0f, -5.0f, -21.0f);
	m_poShips[0].m_vecUp = CVector3(0.0f, -4.0f, -20.0f);
	m_poShips[0].m_vecRight = CVector3(1.0f, -5.0f, -20.0f);
	m_poShips[0].m_vecDirection = m_poShips[0].m_vecHeading;
	m_poShips[0].m_fThrust = 0.0f;
	m_poShips[0].m_fPitch = 0.0f;
	m_poShips[0].m_fYaw = 0.0f;
	m_poShips[0].m_fRoll = 0.0f;
	m_poShips[0].m_fPitchRate = 0.0f;
	m_poShips[0].m_fYawRate = 0.0f;
	m_poShips[0].m_fRollRate = 0.0f;	
	m_poShips[0].m_fMaxPitchRate = 40.0f;
	m_poShips[0].m_fMaxYawRate = 25.0f;
	m_poShips[0].m_fMaxRollRate = 45.0f;	
	m_poShips[0].m_quaOrientation.reset();
	m_poShips[0].m_quaCamOrientation.reset();
	m_poShips[0].m_fDrag = 25.0f;
	m_poShips[0].m_iFlightMode = 1;
	m_poShips[0].m_bWeaponFire = false;

	m_poShips[0].m_poWeapon = new CWeapon(100, CVector3(0.0f, -0.3f, -3.3f)); 
	m_poShips[0].m_poTrail = new CTrail(1000, CVector3(0.0f, -0.5f, 7.2f));
	m_poShips[0].m_poBrake = new CBrake(100, CVector3(0.0f, 0.0f, 0.0f));

	m_poShips[0].m_matRotation.LoadIdentity();
	m_poShips[0].m_matCamRotation.LoadIdentity();
	m_vecTargetPos = CVector3(0.0f, 0.0f, 0.0f);;
}

CAIShip::~CAIShip()
{

}

void CAIShip::simulate(float fDT)
{
	CVector3 vecDistanceMoved, vecMovement, vecTHead = m_poShips[0].m_vecHeading - m_ppMasses[0]->m_vecPos;
	CVector3 vecTRight = m_poShips[0].m_vecRight - m_ppMasses[0]->m_vecPos;
	CVector3 vecTUp = m_poShips[0].m_vecUp - m_ppMasses[0]->m_vecPos;

	m_ppMasses[0]->simulate(fDT);
	//Get unitized vector pointing to target


	//Do speed and direction stuff first
	vecMovement = m_ppMasses[0]->m_vecPos - m_ppMasses[0]->m_vecOldPos;
	//Stores the movement as its used after its unitised
	vecDistanceMoved = vecMovement;
	if (vecMovement.length() == 0.0f)
	{
		m_poShips[0].m_fVel = 0.0f;
		m_poShips[0].m_vecDirection = m_poShips[0].m_vecHeading;
	}
	else
	{
		//calculate velocity, new direction of movement
		m_poShips[0].m_fVel = vecMovement.length() / fDT;
		vecMovement.unitize();
		m_poShips[0].m_vecDirection = vecMovement;
	}

	//temp is the vector from the ai ship to the target, normalised
	CVector3 vecTarget = m_vecTargetPos - m_ppMasses[0]->m_vecPos;
	vecTarget.unitize();


	float fThrust = 0.0f;
	//project temp on to the ships xy plane
	CVector3 vecTemp = vecTarget;
	vecTemp = vecTemp - (vecTRight * vecTRight.dot(vecTemp));

	//calculate the pitch angle from the ships heading
	float fAPitch = vecTHead.dot(vecTemp);

	//Calculate the final pitchrate
	m_poShips[0].m_fPitchRate = acos(fAPitch) * todegrees;

	//Limit the pitchrate to max values
	if (m_poShips[0].m_fPitchRate > m_poShips[0].m_fMaxPitchRate)
		m_poShips[0].m_fPitchRate = m_poShips[0].m_fMaxPitchRate;
	fThrust = m_poShips[0].m_fPitchRate;
	if (m_poShips[0].m_fPitchRate < 3.0f)
		m_poShips[0].m_fPitchRate = 0.0f;
	//Is it a positive or negative angle? 
	float fPAngle = vecTUp.dot(vecTemp);
	if (fPAngle >= 0.0f)
		m_poShips[0].m_fPitchRate = -m_poShips[0].m_fPitchRate;

	//same now for yaw angle
	vecTemp = vecTarget;
	vecTemp.unitize();
	vecTemp = vecTemp - (vecTUp * vecTUp.dot(vecTemp));

	float fAYaw = vecTHead.dot(vecTemp);


	m_poShips[0].m_fYawRate = acos(fAYaw) * todegrees;
	fThrust += m_poShips[0].m_fYawRate;
	if (m_poShips[0].m_fYawRate > m_poShips[0].m_fMaxYawRate)
		m_poShips[0].m_fYawRate = m_poShips[0].m_fMaxYawRate;
	if (m_poShips[0].m_fYawRate < 3.0f)
		m_poShips[0].m_fYawRate = 0.0f;

	float fYAngle = vecTRight.dot(vecTemp);
	if (fYAngle <= 0.0f)
		m_poShips[0].m_fYawRate = -m_poShips[0].m_fYawRate;

	m_poShips[0].m_fThrust = (360.00 - fThrust) * 28.0f;
	if (fThrust < 7.0f)
		m_poShips[0].m_bWeaponFire = true;
	else
		m_poShips[0].m_bWeaponFire = false;

	//Then rotate
	rotate(0, fDT);

	m_poShips[0].m_poTrail->update(fDT, m_poShips[0].m_fThrust, m_ppMasses[0]->m_vecPos, m_poShips[0].m_avecTrailPoints[0], vecDistanceMoved, 
								  m_poShips[0].m_vecUp - m_ppMasses[0]->m_vecPos, m_poShips[0].m_vecRight - m_ppMasses[0]->m_vecPos, 1.5f, 0.5f);
	CVector3 vecGunHead = m_poShips[0].m_vecHeading - m_ppMasses[0]->m_vecPos;
	m_poShips[0].m_poWeapon->update(fDT, vecGunHead, m_poShips[0].m_avecWeaponPoints[0], m_poShips[0].m_fVel, m_poShips[0].m_bWeaponFire);
}


void CAIShip::solve()
{
	CVector3 vecForce, vecDragForce, vecBrakeForce;

	//Normal flight, forces are thrust, drag and braking (if applied)
	vecForce = (m_poShips[0].m_vecHeading - m_ppMasses[0]->m_vecPos) * m_poShips[0].m_fThrust;
	vecDragForce = (m_poShips[0].m_vecDirection * -1 ) * (m_poShips[0].m_fDrag * m_poShips[0].m_fVel);
	m_poShips[0].m_vecForce = vecForce + vecDragForce;

	//apply the force to the ship
	m_ppMasses[0]->applyForce(m_poShips[0].m_vecForce);
}
