// PlayerShip.cpp: implementation of the CPlayerShip class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/PlayerShip.h"
#include "IO/3ds.h"
#include "Sound/SoundManager.h"

using namespace NSDSound;

#include <SDL_opengl.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//In the real thing all ship data will be loaded from file and this
//initialisation will be got from there (or possible from the CShip
//class, This is me a) being lazy, b) being after quick results 
CPlayerShip::CPlayerShip() : 
   CShip(1, 5000.0f),
   m_bInsideView(true),
   m_oLight(GL_LIGHT1),
   m_iThrustChannel(0)
{
   m_ppMasses[0]->m_vecPos = CVector3(0.0f, 0.0f, 0.0f);
   m_ppMasses[0]->m_vecVel = CVector3(0.0f, 0.0f, 0.0f);
   m_poShips[0].m_vecLastForce = CVector3(0.0f, 0.0f, 0.0f);
   m_poShips[0].m_bStraffUp = m_poShips[0].m_bStraffDown = m_poShips[0].m_bStraffLeft = m_poShips[0].m_bStraffRight = false;
   m_poShips[0].m_fDrag = 25.0f;
   m_poShips[0].m_bWeaponFire = false;
   
   m_poShips[0].m_fMaxPitchRate = 40.0f;
   m_poShips[0].m_fMaxYawRate = 25.0f;
   m_poShips[0].m_fMaxRollRate = 45.0f;	

   m_poHud = new CHud();
   m_poShips[0].m_matCamRotation.loadIdentity();
   m_bLeftLook = m_bRightLook = m_bUpLook = m_bBackLook = false;
   
   // Setup cockpit light
   CRGBAColour oAmbient(1.0f, 1.0f, 1.0f, 1.0f);
   CRGBAColour oDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
   CVector3 oPosition(0.0f, 0.0f, 0.0f);
   m_oLight.init(oAmbient, oDiffuse, oPosition);
   
   // Load thruster sound
   int iSample = g_oSoundManager.load("thrust.wav");
   m_iThrustChannel = g_oSoundManager.play(iSample,-1);
   g_oSoundManager.setVolume(0,m_iThrustChannel);
   
   // Setup trails
   m_poShips[0].m_iNumTrails = 2;
   m_poShips[0].m_avecOrigTrailPoints[0] = CVector3(1.6f, -0.25f, 3.75f);
   m_poShips[0].m_avecOrigTrailPoints[1] = CVector3(-1.6f, -0.25f, 3.75f);
   m_poShips[0].m_poTrails = new CTrail[m_poShips[0].m_iNumTrails];
   for (int i=0; i<m_poShips[0].m_iNumTrails; i++)
	  m_poShips[0].m_poTrails[i].setup(250, m_poShips[0].m_avecTrailPoints[i]);


}

CPlayerShip::~CPlayerShip()
{
   delete m_poHud;
}

void CPlayerShip::loadShip()
{
   CLoad3DS oLoad3ds;
   if (oLoad3ds.import3DS(&(m_poShips[0].m_oModel), "Data/Model/shuttle.3ds")) {
      m_poShips[0].m_oModel.init();
   }
   if (oLoad3ds.import3DS(&m_oCockpitModel, "Data/Model/canopy02.3ds")) {
      // Prepare
      m_oCockpitModel.init();
   }

   CShip::loadShip();
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
void CPlayerShip::drawCamera()
{

   CVector3 vecTemp;
   
   
   if (m_bInsideView)
   {
      CMatrix matM(m_poShips[0].m_matRotation);
      matM.invert();
      vecTemp = m_poShips[0].m_vecUp - m_ppMasses[0]->m_vecPos;
      glLoadMatrixf(matM.glElements());
      if (m_bLeftLook)
      {
         glRotatef(-90.0f, vecTemp.X(), vecTemp.Y(), vecTemp.Z());
      }
      else if (m_bRightLook)
      {
         glRotatef(90.0f, vecTemp.X(), vecTemp.Y(), vecTemp.Z());
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
   }
   else 
   {
      CMatrix matC(m_poShips[0].m_matCamRotation);
      matC.invert();
      glLoadMatrixf(matC.glElements());
      glTranslatef(-m_poShips[0].m_vecCamView.X(), -m_poShips[0].m_vecCamView.Y(), -m_poShips[0].m_vecCamView.Z());
   }
        
}

//Needs to be over-ridden in this case. The use of external views means a lot more code
void CPlayerShip::draw()
{

   glPushMatrix();
   glTranslatef(m_ppMasses[0]->m_vecPos.X(), m_ppMasses[0]->m_vecPos.Y(), m_ppMasses[0]->m_vecPos.Z());
   glMultMatrixf(m_poShips[0].m_matRotation.glElements());
   
   //draw the cockpit
   if (m_bInsideView)
   {
      glDisable(GL_LIGHT0);
      m_oLight.enable();
      m_oLight.render();
      m_oCockpitModel.render(); 
      m_oLight.disable();
      glEnable(GL_LIGHT0);
   }
   //draw the ship
   else
      m_poShips[0].m_oModel.render(); 
   
   glPopMatrix();
   
   // Set sound playback location
   g_oSoundManager.setPlaybackLocation(m_ppMasses[0]->m_vecPos, 
                                       m_poShips[0].m_vecUp - m_ppMasses[0]->m_vecPos, 
                                       m_poShips[0].m_vecRight - m_ppMasses[0]->m_vecPos);
   // Set volume
   g_oSoundManager.setVolume(m_poShips[0].m_fThrust/10000.0f,m_iThrustChannel);
   
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
	m_poShips[0].m_matCamRotation = CMatrix(m_poShips[0].m_quaCamOrientation);

	matM = (m_poShips[0].m_matCamRotation);
	m_poShips[0].m_vecCamView = matM * CVector3(0.0f, 0.0f, 20.0f);
	m_poShips[0].m_vecCamView += m_ppMasses[0]->m_vecPos;

}

void CPlayerShip::drawHud()
{
   if (m_bInsideView) {
      if (m_poShips[0].m_poTargetData && m_poShips[0].m_poTargetMass)
         m_poHud->drawTargetData(m_poShips[0].m_poTargetData, m_poShips[0].m_poTargetMass, this);
      m_poHud->draw(m_poShips[0].m_fVel, 300.0f, m_poShips[0].m_fThrust, 9578.0f);
   }
}

