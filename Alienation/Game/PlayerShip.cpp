// PlayerShip.cpp: implementation of the CPlayerShip class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/PlayerShip.h"
#include "IO/3ds.h"
#include "Sound/SoundManager.h"
#include "IO/WeaponFactory.h"

using namespace NSDSound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//In the real thing all ship data will be loaded from file and this
//initialisation will be got from there (or possible from the CShip
//class, This is me a) being lazy, b) being after quick results 
CPlayerShip::CPlayerShip() : 
   CShip(1, 5000.0f),
   m_bInsideView(true),
   m_bLeftLook(false),
   m_bRightLook(false),
   m_bUpLook(false),
   m_bBackLook(false),
   m_poHud(NULL),
   m_iThrustChannel(0)
{
   m_fDrag = 25.0f;
   m_fMaxPitchRate = 40.0f;
   m_fMaxYawRate = 25.0f;
   m_fMaxRollRate = 45.0f;
   

   m_ppMasses[0]->m_vecPos = CVector3(0.0f, 0.0f, 0.0f);
   m_ppMasses[0]->m_vecVel = CVector3(0.0f, 0.0f, 0.0f);

   m_poHud = new CHud(this);
   m_matCamRotation.loadIdentity();
      
   // Load thruster sound
   int iSample = g_oSoundManager.load("thrust.wav");
   m_iThrustChannel = g_oSoundManager.play(iSample,-1);
   g_oSoundManager.setVolume(0,m_iThrustChannel);
   
   // Setup trails
   m_iNumTrails = 2;
   m_avecOrigTrailPoints[0] = CVector3(1.6f, -0.25f, 3.75f);
   m_avecOrigTrailPoints[1] = CVector3(-1.6f, -0.25f, 3.75f);
   m_poTrails = new CTrail[m_iNumTrails];
   for (int i=0; i<m_iNumTrails; i++)
	  m_poTrails[i].setup(250, m_avecTrailPoints[i]);

   // Load weapon
   m_poWeapon = NSDIO::CWeaponFactory::load("ter_ppc2.lua");

}

CPlayerShip::~CPlayerShip()
{
   delete m_poHud;
}

void CPlayerShip::load()
{
   NSDIO::CLoad3DS oLoad3ds;
   if (oLoad3ds.import3DS(&(m_oModel), "shuttle.3ds")) {
      m_oModel.init();
   }
   if (oLoad3ds.import3DS(&m_oCockpitModel, "canopy02.3ds")) {
      // Prepare
      m_oCockpitModel.init();
   }

   CShip::load();
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
      CMatrix matM(m_matRotation);
      matM.invert();
      vecTemp = m_vecUp - m_ppMasses[0]->m_vecPos;
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
         vecTemp = m_vecRight - m_ppMasses[0]->m_vecPos;
         glRotatef(-90.0f, vecTemp.X(), vecTemp.Y(), vecTemp.Z());
      }
      glTranslatef(-m_ppMasses[0]->m_vecPos.X(), -m_ppMasses[0]->m_vecPos.Y(), -m_ppMasses[0]->m_vecPos.Z()); 
   }
   else 
   {
      CMatrix matC(m_matCamRotation);
      matC.invert();
      glLoadMatrixf(matC.glElements());
      glTranslatef(-m_vecCamView.X(), -m_vecCamView.Y(), -m_vecCamView.Z());
   }
        
}

//Needs to be over-ridden in this case. The use of external views means a lot more code
void CPlayerShip::draw(bool bTestFrustum)
{

   if (!m_bInsideView)
   {
      glPushMatrix();
      glTranslatef(m_ppMasses[0]->m_vecPos.X(), m_ppMasses[0]->m_vecPos.Y(), m_ppMasses[0]->m_vecPos.Z());
      glMultMatrixf(m_matRotation.glElements());   
      m_oModel.render(); 
      glPopMatrix();
   }
   
   // Set sound playback location
   g_oSoundManager.setPlaybackLocation(m_ppMasses[0]->m_vecPos, 
                                       m_vecUp - m_ppMasses[0]->m_vecPos, 
                                       m_vecRight - m_ppMasses[0]->m_vecPos);
   // Set volume
   g_oSoundManager.setVolume(m_fThrust/10000.0f,m_iThrustChannel);
   
}

//Calcuates the external view camera
void CPlayerShip::rotateCam(float fDT)
{
	;
	CMatrix matM;
	float fPitch = 0.0f, fYaw = 0.0f;

	if (m_fCamPitch)
	{
		fPitch = fDT * m_fCamPitch;		//change in pitch rate over time
	}

	if (m_fCamYaw)
	{
		fYaw = fDT * m_fCamYaw;			//change in yaw rate over time
	}

	CQuat quaTemp(DEG_TO_RAD(fYaw), 0.0f, DEG_TO_RAD(fPitch));
	quaTemp *= m_quaCamOrientation;
	m_quaCamOrientation = quaTemp;
	m_matCamRotation = CMatrix(m_quaCamOrientation);

	matM = (m_matCamRotation);
	m_vecCamView = matM * CVector3(0.0f, 0.0f, 20.0f);
	m_vecCamView += m_ppMasses[0]->m_vecPos;

}

void CPlayerShip::drawHud()
{
   if (m_bInsideView) {
      glPushMatrix();
      glTranslatef(m_ppMasses[0]->m_vecPos.X(), m_ppMasses[0]->m_vecPos.Y(), m_ppMasses[0]->m_vecPos.Z());
      glMultMatrixf(m_matRotation.glElements());   
      //draw the cockpit
      m_oCockpitModel.render(); 
      glPopMatrix();
      m_poHud->render();
   }
}

void CPlayerShip::renderOffScreen()
{
   if (m_bInsideView) {
      m_poHud->renderOffScreen();
   }
}

void CPlayerShip::setTarget(CGameObject *pTarget) 
{
   m_poHud->setTarget(pTarget);
}
