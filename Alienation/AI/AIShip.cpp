// AIShip.cpp: implementation of the CAIShip class.
//
//////////////////////////////////////////////////////////////////////

#include "AIShip.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CAIShip::CAIShip(float mass) :
   CShip(mass),
   m_fXAngle(0.0f),
   m_fYAngle(0.0f)
{
}

CAIShip::~CAIShip()
{

}

void CAIShip::simulate(float fDT)
{
	CVector3 vecTHead = m_vecHeading - m_ppMasses[0]->m_vecPos;
	CVector3 vecTRight = m_vecRight - m_ppMasses[0]->m_vecPos;
	CVector3 vecTUp = m_vecUp - m_ppMasses[0]->m_vecPos;

	//Get normalised vector pointing to target

	//vecTarget is the vector from the ai ship to the target, normalised
	CVector3 vecTarget = m_poTarget->m_ppMasses[0]->m_vecPos - m_ppMasses[0]->m_vecPos;
	vecTarget.normalise();


	float fThrust = 0.0f;
	//project temp on to the ships xy plane
	CVector3 vecTemp = vecTarget;
	vecTemp = vecTemp - (vecTRight * vecTRight.dot(vecTemp));

	//calculate the pitch angle from the ships heading
	float fAPitch = vecTHead.dot(vecTemp);

	//Calculate the final pitchrate
	m_fPitchRate = RAD_TO_DEG(acos(fAPitch));

	//Limit the pitchrate to max values
	if (m_fPitchRate > m_fMaxPitchRate)
		m_fPitchRate = m_fMaxPitchRate;
	fThrust = m_fPitchRate;
	if (m_fPitchRate < 3.0f)
		m_fPitchRate = 0.0f;
	//Is it a positive or negative angle? 
	float fPAngle = vecTUp.dot(vecTemp);
	if (fPAngle >= 0.0f)
		m_fPitchRate = -m_fPitchRate;

	//same now for yaw angle
	vecTemp = vecTarget;
	vecTemp.normalise();
	vecTemp = vecTemp - (vecTUp * vecTUp.dot(vecTemp));

	float fAYaw = vecTHead.dot(vecTemp);


	m_fYawRate = RAD_TO_DEG(acos(fAYaw));
	fThrust += m_fYawRate;
	if (m_fYawRate > m_fMaxYawRate)
		m_fYawRate = m_fMaxYawRate;
	if (m_fYawRate < 3.0f)
		m_fYawRate = 0.0f;

	float fYAngle = vecTRight.dot(vecTemp);
	if (fYAngle <= 0.0f)
		m_fYawRate = -m_fYawRate;

	m_fThrust = (360.00 - fThrust) * 28.0f;
	if (fThrust < 7.0f)
		m_bWeaponFire = true;
	else
		m_bWeaponFire = false;


	CShip::simulate(fDT);
}


void CAIShip::solve()
{
	CVector3 vecForce, vecDragForce;

	//Normal flight, forces are thrust, drag and braking (if applied)
	vecForce = (m_vecHeading - m_ppMasses[0]->m_vecPos) * m_fThrust;
	vecDragForce = (m_vecDirection * -1 ) * (m_fDrag * m_fVel);
	m_vecForce = vecForce + vecDragForce;

	//apply the force to the ship
	m_ppMasses[0]->applyForce(m_vecForce);
}

