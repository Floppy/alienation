// Ship.cpp: implementation of the CGameObject class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/Ship.h"
#include "IO/3ds.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGameObject::CGameObject(int num, float mass) : CSimulation(num, mass)
{
   //initialise data
   m_ppMasses[0]->m_vecVel = CVector3(0.0f, 0.0f, 0.0f);
   m_vecHeading = CVector3(0.0f, -2.0f, -11.0f);
   m_fPitch = 0.0f;
   m_fYaw = 0.0f;
   m_fRoll = 0.0f;
   m_quaOrientation.loadIdentity();
   m_fPitchRate = 0.0f;
   m_fYawRate = 0.0f;
   m_fRollRate = 0.0f;	
   m_fVel = 0.0f;
   m_fDrag = 0.025f;
   m_poTarget = NULL;

   m_matRotation.loadIdentity();
}

CGameObject::~CGameObject()
{
}


//what it says on the tin
void CGameObject::draw(bool bTestFrustum)
{
   m_oModel.boundingSphere().m_vecPos = m_ppMasses[0]->m_vecPos;
   if (bTestFrustum && !m_oFrustum.SphereInFrustum(&m_oModel.boundingSphere())) return;
   
   glPushMatrix();
   glTranslatef(m_ppMasses[0]->m_vecPos.X(), 
                m_ppMasses[0]->m_vecPos.Y(), 
                m_ppMasses[0]->m_vecPos.Z());
   glMultMatrixf(m_matRotation.glElements());

   m_oModel.render(); //draw the ship
   
   glPopMatrix();

}

void CGameObject::rotate(float fDT)
{
	float fPitch = 0.0f, fYaw = 0.0f, fRoll = 0.0f;

	if (m_fPitchRate)
	{
		fPitch = fDT * m_fPitchRate;		//change in pitch rate over time
	}

	if (m_fYawRate)
	{
		fYaw = fDT * m_fYawRate;			//change in yaw rate over time
	}

	if (m_fRollRate)
	{
		fRoll = fDT * m_fRollRate;		//change in roll rate over time
	}


	CQuat quaTemp(DEG_TO_RAD(fYaw), DEG_TO_RAD(fRoll), DEG_TO_RAD(fPitch));
	quaTemp *= m_quaOrientation;
	m_quaOrientation = quaTemp;
	m_matRotation = CMatrix(m_quaOrientation);

	rotHeading(m_matRotation);

}

void CGameObject::rotHeading(CMatrix mat)
{
	m_vecHeading          = mat * CVector3( 0.0f, 0.0f,-1.0f) + m_ppMasses[0]->m_vecPos;
	m_vecUp               = mat * CVector3( 0.0f, 1.0f, 0.0f) + m_ppMasses[0]->m_vecPos;
	m_vecRight            = mat * CVector3( 1.0f, 0.0f, 0.0f) + m_ppMasses[0]->m_vecPos;
}

//Applies the time based update
void CGameObject::simulate(float fDT)
{
	CVector3	vecMovement, vecDistanceMoved;

	CSimulation::simulate (fDT);

	//get the amount of movement to calculate speed
	vecMovement = m_ppMasses[0]->m_vecPos - m_ppMasses[0]->m_vecOldPos;
	//Stores the movement as its used after its unitised
	vecDistanceMoved = vecMovement;

	//Not moved? velocity = 0;
	if (vecMovement.length() == 0.0f)
	{
		m_fVel = 0.0f;
		m_vecDirection = m_vecHeading;
	}
	else
	{
		//calculate velocity, new direction of movement
		m_fVel = vecMovement.length() / fDT;
		vecMovement.normalise();
		m_vecDirection = vecMovement;
	}

	//Perform rotation to ship 0
	rotate (fDT);

}
