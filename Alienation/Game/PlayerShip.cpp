// PlayerShip.cpp: implementation of the CPlayerShip class.
//
//////////////////////////////////////////////////////////////////////

#include "Game/PlayerShip.h"
#include "Sound/SoundManager.h"

using namespace NSDSound;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//In the real thing all ship data will be loaded from file and this
//initialisation will be got from there (or possible from the CShip
//class, This is me a) being lazy, b) being after quick results 
CPlayerShip::CPlayerShip(float mass) : 
   CShip(mass),
   m_bInsideView(true),
   m_bLeftLook(false),
   m_bRightLook(false),
   m_bUpLook(false),
   m_bBackLook(false),
   m_iThrustChannel(0),      
   m_iLastTime(SDL_GetTicks()),
   m_oLight(GL_LIGHT1)

{
   // Setup light
   CRGBAColour oLightAmbient(1.0f, 1.0f, 1.0f, 1.0f);
   CRGBAColour oLightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
   CVector3 oPosition(1000.0f, 1000.0f, -1000.0f);
   m_oLight.init(oLightAmbient, oLightDiffuse, oPosition);

	m_poRadar = new CRadar();
	m_poRadar->init();
	m_poRadar->init2D(0.4f, 0.7f, 0.2f, 0.2f, "");
	m_poRadar->setRange(25000);
   m_matCamRotation.loadIdentity();
      
   // Load thruster sound
   int iSample = g_oSoundManager.load("thrust.wav");
   m_iThrustChannel = g_oSoundManager.play(iSample,-1);
   g_oSoundManager.setVolume(0,m_iThrustChannel);
   
}

CPlayerShip::~CPlayerShip()
{
   for (vector<CShield*>::iterator it = m_lShields.begin(); it != m_lShields.end(); it++) {
      delete *it;
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

      glEnable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      
      m_oLight.enable();
      m_oLight.render();

      // Render shields
      for (vector<CShield*>::iterator it = m_lShields.begin(); it != m_lShields.end(); it++) {
         (*it)->renderQuad();
      }

      float fMaxSpeed(300.0f);
      float fMaxThrust(9578.0f);
      
      float fWidthSpeed = (m_fVel == 0.0f) ?
         0.001f :
         (m_fVel / fMaxSpeed) + 0.001f;
      
      float fWidthThrust = (m_fThrust == 0.0f) ? 
         0.001f : 
         (m_fThrust / fMaxThrust) + 0.001f;


      // Draw engine info
      m_poSpeedIndicator->setTexturePercentage(fWidthSpeed);
      m_poSpeedIndicator->renderQuad();
//      sprintf(strFont,"Velocity: %.1f", m_fVel);
//      m_poFont->print(strFont, CVector2(420.0f, 210.0f), 5.0f);
      m_poThrustIndicator->setTexturePercentage(fWidthThrust);      
      m_poThrustIndicator->renderQuad();
//      sprintf(strFont,"Thrust: %.1f", m_fThrust);
//      m_poFont->print(strFont, CVector2(420.0f, 560.0f), 5.0f);

      // Draw target information
      m_poTargetingComputer->render();


      // Calc FPS
      char strFont[20];
      unsigned long iTime = SDL_GetTicks();
      unsigned long iFPS = 0;
      if (iTime != m_iLastTime) {
         iFPS = 1000/(iTime - m_iLastTime);
      }
      sprintf(strFont,"%3ld FPS", iFPS);
//      m_poFont->print(strFont, CVector2(900.0f, 20.0f), 5.0f);
      m_iLastTime = iTime;
      
      // Draw radar
      m_poRadar->render();

      m_oLight.disable();

      glDisable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);


   }

}

void CPlayerShip::renderOffScreen()
{
   if (m_bInsideView) {
      m_oLight.enable();
      m_oLight.render();
      m_poTargetingComputer->renderOffScreen();
      m_poRadar->renderOffScreen(this->m_ppMasses[0]->m_vecPos);
      m_oLight.disable();
   }
}

void CPlayerShip::setTarget(CGameObject *pTarget) 
{
   CGameObject::setTarget(pTarget);
   m_poTargetingComputer->setTarget(m_poTarget);
   m_poRadar->setTarget(m_poTarget->getObjectID());
}

void CPlayerShip::addTarget(CGameObject *pTarget)
{
   m_poRadar->addTarget(pTarget->getObjectID(), pTarget->getObjectType(), pTarget->m_ppMasses[0]->m_vecPos);
}

void CPlayerShip::clearTargetList()
{
   m_poRadar->clearTargetList();
}
