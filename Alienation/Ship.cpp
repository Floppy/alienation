// Ship.cpp: implementation of the CShip class.
//
//////////////////////////////////////////////////////////////////////

#include "Ship.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShip::CShip(int num, float mass) : CSimulation(num, mass)
{
	//initialise data
	m_poShips = new CShipData[1];
	m_ppMasses[0]->m_vecPos = CVector3(-5.0f, -0.0f, -20.0f);
	m_ppMasses[0]->m_vecVel = CVector3(0.0f, 0.0f, 0.0f);
	m_poShips[0].m_avecTrailPoints[0] = CVector3(0.0f, 0.0f, 7.0f);
	m_poShips[0].m_vecHeading = CVector3(0.0f, -2.0f, -11.0f);
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
	m_poShips[0].m_fDrag = 0.025f;
	m_poShips[0].m_iFlightMode = 1;

	m_poShips[0].m_poTrail = new CTrail(1000, CVector3(0.0f, -0.5f, 7.2f));
	m_poShips[0].m_poWeapon = new CWeapon(100, CVector3(0.0f, -0.3f, -3.3f)); 
	m_poShips[0].m_poBrake = new CBrake(100, CVector3(.0.f, 0.0f, 0.0f));

	m_poShips[0].m_matRotation.LoadIdentity();
}

CShip::~CShip()
{

}

//load model, trail texture and brake texture
void CShip::loadShip()
{
	m_poShips[0].m_oModel.init3ds("data/model/shuttle/shuttle.3ds");
	m_poShips[0].m_poTrail->init();
	m_poShips[0].m_poBrake->init();
}

//what it says on the tin
void CShip::draw()
{
	CVector3 vecTemp;

	glPushMatrix();					//Save copy of lookat rotation
	glTranslatef(m_ppMasses[0]->m_vecPos.m_fx, m_ppMasses[0]->m_vecPos.m_fy, m_ppMasses[0]->m_vecPos.m_fz); //move to ship position
	glMultMatrixf(m_poShips[0].m_matRotation.m_afElement); //multiply by the ships rotation matrix
	m_poShips[0].m_oModel.render3ds(); //draw the ship

	glPopMatrix(); // Make the gluLookat matrix again active

}

//This function calculates the force acting on the ship
void CShip::solve()
{
	CVector3 vecForce, vecDragForce, vecBrakeForce;

	if (m_poShips[0].m_iFlightMode == 1)
	{
		//Normal flight, forces are thrust, drag and braking (if applied)
		vecForce = (m_poShips[0].m_vecHeading - m_ppMasses[0]->m_vecPos) * m_poShips[0].m_fThrust;
		vecDragForce = (m_poShips[0].m_vecDirection * -1 ) * (m_poShips[0].m_fDrag * m_poShips[0].m_fVel);
		if (m_poShips[0].m_bBraking && m_poShips[0].m_fVel != 0.0f)
		{
			vecBrakeForce = (m_poShips[0].m_vecDirection * -1 ) * 3000;
		}
		else
		{
			vecBrakeForce = CVector3(0.0f, 0.0f, 0.0f);
		}
		m_poShips[0].m_vecForce = vecForce + vecDragForce;
		m_poShips[0].m_vecForce += vecBrakeForce;
		//The last force applied is stored in case the user switches to straff mode
		m_poShips[0].m_vecLastForce = m_poShips[0].m_vecForce;

	}

	//Turret mode, absolutely no forces applied, ship just drifts
	if (m_poShips[0].m_iFlightMode == 2)
	{
		m_poShips[0].m_vecForce = CVector3(0.0f, 0.0f, 0.0f);

		m_poShips[0].m_fThrust = 0.0f;
	}

	//Straff mode. The length of the last force is applied in the
	//direction of the joystick (amended, doubled the last force to 
	//make the effect more noticable)
	if (m_poShips[0].m_iFlightMode == 3)
	{
		m_poShips[0].m_fThrust = 0.0f;
		CVector3 vecTemp = CVector3(0.0f, 0.0f, 0.0f);
		float fLen = m_poShips[0].m_vecLastForce.length() * 2.0f;

		if (m_poShips[0].m_bStraffDown)
		{
			vecTemp += (m_poShips[0].m_vecUp - m_ppMasses[0]->m_vecPos) * - fLen;
		}
		if (m_poShips[0].m_bStraffUp)
		{
			vecTemp += (m_poShips[0].m_vecUp - m_ppMasses[0]->m_vecPos) * fLen;
		}
		if (m_poShips[0].m_bStraffRight)
		{
			vecTemp += (m_poShips[0].m_vecRight - m_ppMasses[0]->m_vecPos) * fLen;
		}
		if (m_poShips[0].m_bStraffLeft)
		{
			vecTemp += (m_poShips[0].m_vecRight - m_ppMasses[0]->m_vecPos) * -fLen;
		}
		m_poShips[0].m_vecForce = vecTemp;
	}
	//apply the force to the ship
	m_ppMasses[0]->applyForce(m_poShips[0].m_vecForce);
}

//Applies the time based update
void CShip::simulate(float fDT)
{
	CVector3	vecMovement, vecDistanceMoved, vecGunHead;

	CSimulation::simulate (fDT);

	//get the amount of movement to calculate speed
	vecMovement = m_ppMasses[0]->m_vecPos - m_ppMasses[0]->m_vecOldPos;
	//Stores the movement as its used after its unitised
	vecDistanceMoved = vecMovement;

	//Not moved? velocity = 0;
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

	//Perform rotation to ship 0
	rotate (0, fDT);

	//update trail, weapons and heading
	m_poShips[0].m_poTrail->update(fDT, m_poShips[0].m_fThrust, m_ppMasses[0]->m_vecPos, m_poShips[0].m_avecTrailPoints[0], vecDistanceMoved, 
								  m_poShips[0].m_vecUp - m_ppMasses[0]->m_vecPos, m_poShips[0].m_vecRight - m_ppMasses[0]->m_vecPos, 1.5f, 0.5f);
	vecGunHead = m_poShips[0].m_vecHeading - m_ppMasses[0]->m_vecPos;
	m_poShips[0].m_poWeapon->update(fDT, vecGunHead, m_poShips[0].m_avecWeaponPoints[0], m_poShips[0].m_fVel, m_poShips[0].m_bWeaponFire);
	m_poShips[0].m_poBrake->update(fDT, m_ppMasses[0]->m_vecPos, m_poShips[0].m_vecDirection, m_poShips[0].m_vecBrakePoint, m_poShips[0].m_bBraking);
}


void CShip::rotate(int iShip, float fDT)
{
	CQuat quaTemp;
	float fPitch = 0.0f, fYaw = 0.0f, fRoll = 0.0f;

	if (m_poShips[iShip].m_fPitchRate)
	{
		fPitch = fDT * m_poShips[iShip].m_fPitchRate;		//change in pitch rate over time
	}

	if (m_poShips[iShip].m_fYawRate)
	{
		fYaw = fDT * m_poShips[iShip].m_fYawRate;			//change in yaw rate over time
	}

	if (m_poShips[iShip].m_fRollRate)
	{
		fRoll = fDT * m_poShips[iShip].m_fRollRate;		//change in roll rate over time
	}


	quaTemp.eulerToQuat(fYaw * piover180, fRoll * piover180, fPitch * piover180);
	quaTemp.multQuat(m_poShips[iShip].m_quaOrientation);
	m_poShips[iShip].m_quaOrientation.copyQuat(quaTemp);
	m_poShips[iShip].m_matRotation.QuatToMatrix(m_poShips[0].m_quaOrientation);

	rotHeading(m_poShips[0].m_matRotation);

}




void CShip::rotHeading(CMatrix mat)
{

	m_poShips[0].m_vecHeading = mat.MultMatrixVector(CVector3(0.0f, 0.0f, -1.0f));
	m_poShips[0].m_vecUp = mat.MultMatrixVector(CVector3(0.0f, 1.0f, 0.0f));
	m_poShips[0].m_vecRight = mat.MultMatrixVector(CVector3(1.0f, 0.0f, 0.0f));
	m_poShips[0].m_avecWeaponPoints[0] = mat.MultMatrixVector(CVector3(0.0f, -0.7f, -7.3f));
	m_poShips[0].m_avecTrailPoints[0] = (m_poShips[0].m_vecHeading * -6.7f) + ((m_poShips[0].m_vecUp * -1) * 0.37f);
	m_poShips[0].m_vecBrakePoint = mat.MultMatrixVector(CVector3(0.0f, 0.7f, -2.5f));

	m_poShips[0].m_vecHeading += m_ppMasses[0]->m_vecPos;
	m_poShips[0].m_vecUp += m_ppMasses[0]->m_vecPos;
	m_poShips[0].m_vecRight += m_ppMasses[0]->m_vecPos;
	m_poShips[0].m_avecTrailPoints[0] += m_ppMasses[0]->m_vecPos;
	m_poShips[0].m_vecCamView += m_ppMasses[0]->m_vecPos;
	m_poShips[0].m_avecWeaponPoints[0] += m_ppMasses[0]->m_vecPos;
	m_poShips[0].m_vecBrakePoint += m_ppMasses[0]->m_vecPos;
}

void CShip::drawTrail()
{
	if (m_poShips[0].m_fThrust == 0.0f)
		return;

	m_poShips[0].m_poTrail->render(m_poShips[0].m_fThrust, m_poShips[0].m_avecTrailPoints[0]);
}

void CShip::drawWeapons()
{
	m_poShips[0].m_poWeapon->render();
}

void CShip::drawBrake()
{
	m_poShips[0].m_poBrake->render();
}