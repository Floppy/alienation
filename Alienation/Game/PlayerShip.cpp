// PlayerShip.cpp: implementation of the CPlayerShip class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/PlayerShip.h"
#include "IO/3ds.h"

#include <GL/gl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//In the real thing all ship data will be loaded from file and this
//initialisation will be got from there (or possible from the CShip
//class, This is me a) being lazy, b) being after quick results 
CPlayerShip::CPlayerShip() : 
   CShip(1, 5000.0f),
   m_bInsideView(true),
   m_oLight(GL_LIGHT1)
{
	m_ppMasses[0]->m_vecPos = CVector3(0.0f, 0.0f, 0.0f);
	m_ppMasses[0]->m_vecVel = CVector3(0.0f, 0.0f, 0.0f);
	m_poShips[0].m_vecLastForce = CVector3(0.0f, 0.0f, 0.0f);
	m_poShips[0].m_bStraffUp = m_poShips[0].m_bStraffDown = m_poShips[0].m_bStraffLeft = m_poShips[0].m_bStraffRight = false;
	m_poShips[0].m_fDrag = 25.0f;
	m_poShips[0].m_bWeaponFire = false;

	m_poHud = new CHud();
	m_poShips[0].m_matCamRotation.LoadIdentity();
	m_bLeftLook = m_bRightLook = m_bUpLook = m_bBackLook = false;

        // Setup cockpit light
        CRGBAColour oAmbient(1.0f, 1.0f, 1.0f, 1.0f);
        CRGBAColour oDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
        CVector3 oPosition(0.0f, 0.0f, 0.0f);
	m_oLight.init(oAmbient, oDiffuse, oPosition);

}

CPlayerShip::~CPlayerShip()
{
   delete m_poHud;
}

void CPlayerShip::loadShip()
{
   CShip::loadShip();
   CLoad3DS oLoad3ds;
   if (oLoad3ds.import3DS(&m_oCockpitModel, "Data/Model/canopy02.3ds")) {
      // Prepare
      m_oCockpitModel.init();
   }
}

//At last!! using inheritance! Only extra thing this does is rotate the camera
//the same as the ship
void CPlayerShip::simulate(float fDT)
{

	CShip::simulate(fDT);

	if (!m_bInsideView)
	{
		rotateCam(fDT);
	}
}

//Needs to be over-ridden in this case. The use of external views means a lot more code
void CPlayerShip::draw()
{

	CMatrix matM, matC;
	CVector3 vecTemp;

	matM.CopyMatrix(m_poShips[0].m_matRotation.m_afElement);
	matM.MatrixInverse();
	matC.CopyMatrix(m_poShips[0].m_matCamRotation.m_afElement);
	matC.MatrixInverse();

	if (m_bInsideView)
	{
		vecTemp = m_poShips[0].m_vecUp - m_ppMasses[0]->m_vecPos;
		glLoadMatrixf(matM.m_afElement);
		if (m_bLeftLook)
		{
			glRotatef(-90.0f, vecTemp.X(), vecTemp.Y(), vecTemp.Z());
		}
		else if (m_bRightLook)
                {
                   glRotatef(90.0f, vecTemp.Z(), vecTemp.Y(), vecTemp.Z());
                }
                else if (m_bBackLook)
                {
                   glRotatef(180.0f, vecTemp.X(), vecTemp.Y(), vecTemp.Z());
                }
		else if (m_bUpLook)
                {
                   vecTemp = m_poShips[0].m_vecRight - m_ppMasses[0]->m_vecPos;
                   glRotatef(-90.0f, vecTemp.X(), vecTemp.Y(), vecTemp.Z());
                }
		glTranslatef(-m_ppMasses[0]->m_vecPos.X(), -m_ppMasses[0]->m_vecPos.Y(), -m_ppMasses[0]->m_vecPos.Z()); 
		glPushMatrix();
		glTranslatef(m_ppMasses[0]->m_vecPos.X(), m_ppMasses[0]->m_vecPos.Y(), m_ppMasses[0]->m_vecPos.Z());
		glMultMatrixf(m_poShips[0].m_matRotation.m_afElement);

                glDisable(GL_LIGHT0);
                m_oLight.enable();
                m_oCockpitModel.render(); //draw the cockpit
                m_oLight.disable();
                glEnable(GL_LIGHT0);
		glPopMatrix();
	}

	
	if (!m_bInsideView)
	{
		glLoadMatrixf(matC.m_afElement);
		glTranslatef(-m_poShips[0].m_vecCamView.X(), -m_poShips[0].m_vecCamView.Y(), -m_poShips[0].m_vecCamView.Z());
		glPushMatrix();
		glTranslatef(m_ppMasses[0]->m_vecPos.X(), m_ppMasses[0]->m_vecPos.Y(), m_ppMasses[0]->m_vecPos.Z());
		glMultMatrixf(m_poShips[0].m_matRotation.m_afElement);
		m_poShips[0].m_oModel.render(); //draw the ship
		glPopMatrix();
	}

}

//Calcuates the external view camera
void CPlayerShip::rotateCam(float fDT)
{
	;
	CMatrix matM;
	float fPitch = 0.0f, fYaw = 0.0f;

	if (m_poShips[0].m_fCamPitch)
	{
		fPitch = fDT * m_poShips[0].m_fCamPitch;		//change in pitch rate over time
	}

	if (m_poShips[0].m_fCamYaw)
	{
		fYaw = fDT * m_poShips[0].m_fCamYaw;			//change in yaw rate over time
	}

	CQuat quaTemp(DEG_TO_RAD(fYaw), 0.0f, DEG_TO_RAD(fPitch));
	quaTemp *= m_poShips[0].m_quaCamOrientation;
	m_poShips[0].m_quaCamOrientation = quaTemp;
	m_poShips[0].m_matCamRotation.QuatToMatrix(m_poShips[0].m_quaCamOrientation);

	matM.CopyMatrix(m_poShips[0].m_matCamRotation.m_afElement);
	m_poShips[0].m_vecCamView = matM.MultMatrixVector(CVector3(0.0f, 0.0f, 20.0f));	
	m_poShips[0].m_vecCamView += m_ppMasses[0]->m_vecPos;

}

void CPlayerShip::drawHud()
{
	m_poHud->drawHoloTarget(m_poShips[0].m_poTargetData, m_poShips[0].m_poTargetMass, this);
	m_poHud->draw(m_poShips[0].m_fVel, 300.0f, m_poShips[0].m_fThrust, 9578.0f);
}
