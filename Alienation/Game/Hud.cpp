#include "Game/Hud.h"
#include "3D/TextureManager.h"
#include <SDL.h>
#include <SDL_opengl.h>

//namespace NSD2D {

   CHud::CHud(CShip* pPlayerShip) :
      m_pPlayerShip(pPlayerShip),
      m_pTarget(NULL),
      m_iLastTime(SDL_GetTicks()),
      m_oLight(GL_LIGHT1)
   {
//     for (int i=0; i<9; i++) {
//         m_auiTextures[i] = 0;
//      }
      init();
   }
   
   CHud::~CHud()
   {
//      for (int i=0; i<9; i++) {
         g_oTextureManager.removeReference(m_auiOffScreenTexture);
//      }
   }


   //**************************************************************************************
   // Function name    : CHud::draw
   // Author           : Gary Ingram
   // Return type      : void 
   // Date Created     : 25/05/2003
   // Description      : Draws the ship hud including all the information relevent to 
   //                    the player ship. Will be enlarged over time to include 
   //                    more ship information. 
   // History
   //   Version         Date         Who      Description
   //   =======         ====         ===      ===========
   //     1.0           25/05/2003   GI       Initial Version
   //     1.1           26/05/2003   GI       Using glOrtho to display hud as a 
   //                                         proper 2d surface  
   //     1.2           14/06/2003   JS       Sets the material properties properly 
   //                                         now using new class   
   //     1.3           14/06/2003   GI       Now drawn using 2d object class.  
   //     1.4           24/08/2003   JS       Removed arguments, all info comes from members.
   //**************************************************************************************
   void CHud::render()
   {   
      double modelview[16];
      double projection[16];
      
      glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
      glGetDoublev(GL_PROJECTION_MATRIX,projection);

      float fMaxSpeed(300.0f);
      float fMaxThrust(9578.0f);
      
      char strFont[20];
      float fWidthSpeed, fWidthThrust;
      CVector2 avecTex[4];
      
      //////////////////////////////////////////////
      //Calculate the size of the textures for    //
      //the ships speed and thrust. This diplays  //
      //a part of the thrust/speed texture as a   //
      //percentage of maximum thrust/speed. Will  //
      //be seperated out into a seperate          //
      //function soon as will need a lot more     //
      //like this (Shields armor etc)             //
      //////////////////////////////////////////////
      
      if (m_pPlayerShip->m_fVel == 0.0f)
      {
         fWidthSpeed = 0.001f;
      }
      else
      {
         fWidthSpeed = (m_pPlayerShip->m_fVel / fMaxSpeed) + 0.001f;
      }
      
      if (m_pPlayerShip->m_fThrust == 0.0f)
      {
         fWidthThrust = 0.001f;
      }
      else
      {
         fWidthThrust = (m_pPlayerShip->m_fThrust / fMaxThrust) + 0.001f;
      }

      //////////////////////////////////////////////
      //NEW!!! Now using goOrtho to display the   //
      //hud. This is in 2d so no worries over z   //
      //depth etc                                 //
      //////////////////////////////////////////////
      
      //////////////////////////////////////////////
      //First store the modelview matrix and      //
      //then reset it, then store the projection  //
      //matrix and reset it, finally set up the   //
      //2D ortho view                             //
      //////////////////////////////////////////////
      
      
      //////////////////////////////////////////////
      //Texture and blending stuff manually sets  //
      //the material properties. Hard coded,      //
      //shouldnt be really                        //
      //////////////////////////////////////////////

      glEnable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//      m_oMaterial.render();
      
      //////////////////////////////////////////////
      //Target Data                               //
      //////////////////////////////////////////////

/*      if (m_pTarget) {
         // Set quad
         avecTex[0] = CVector2( 0.0f, 0.0f);
         avecTex[1] = CVector2( 1.0f, 0.0f);
         avecTex[2] = CVector2( 1.0f, 1.0f);
         avecTex[3] = CVector2( 0.0f, 1.0f);
         // Select targeting reticle
         g_oTextureManager.render(m_auiTextures[8]);
         CVector3 pos = m_pTarget->m_ppMasses[0]->m_vecPos;
         // Get viewport
         int viewport[4];
         glGetIntegerv(GL_VIEWPORT,viewport);
         // Project to 2d screen coords
         double dX, dY, dZ;
         gluProject(pos.X(),pos.Y(),pos.Z(),
                    modelview, projection,
                    viewport, &dX, &dY, &dZ);
         // If behind, invert and scale everything up lots to force it to the edge
         // This could perhaps work better... not too happy, but it's late
         if (dZ > 1.0f) {
            dX = -(dX - (viewport[2]/2)) * viewport[2] + viewport[2]/2;
            dY = -(dY - (viewport[3]/2)) * viewport[3] + viewport[3]/2;
         }
         // Clip
         if (dX < 0) dX = 0;
         else if (dX > viewport[2]) dX = viewport[2];
         if (dY < 0) dY = 0;
         else if (dY > viewport[3]) dY = viewport[3];         
         // Rescale to 1024*768
         dX /= viewport[2];
         dY /= viewport[3];
         dX *= 1024.0f;
         dY *= 768.0f;
         // Render reticle
//         m_po2DObject->renderQuad(dX-32.0f, (viewport[3]-dY)+32.0f, 64.0f, 64.0f, avecTex);
         // Calculate range
		 NSDMath::CVector3 vecTarget = m_pTarget->m_ppMasses[0]->m_vecPos - m_pPlayerShip->m_ppMasses[0]->m_vecPos;
         int iRange = static_cast<int>(vecTarget.length());           
         // Range
         sprintf(strFont,"%5d m", iRange);
//         m_poFont->print("Range:", CVector2(50.0f, 220.0f), 5.0f);
//         m_poFont->print(strFont, CVector2(50.0f, 240.0f), 5.0f);
         // Velocity
         sprintf(strFont,"%5d m/s", static_cast<int>(m_pTarget->m_fVel));
//         m_poFont->print("Velocity:", CVector2(50.0f, 260.0f), 5.0f);
//         m_poFont->print(strFont, CVector2(50.0f, 280.0f), 5.0f);
         // Radar image
         g_oTextureManager.render(m_auiTextures[7]);
//         m_po2DObject->renderQuad(37.0f, 180.0f, 135.0f, 135.0f, avecTex);
      }
*/      
      //////////////////////////////////////////////
      //Right Shield                              //
      //////////////////////////////////////////////
      
      m_poFrontShield->renderQuad();
      m_poRightShield->renderQuad();
      m_poLeftShield->renderQuad();
      m_poRearShield->renderQuad();

	  m_poSpeedIndicator->setTexturePercentage(fWidthSpeed);
	  m_poThrustIndicator->setTexturePercentage(fWidthThrust);

	  m_poSpeedIndicator->renderQuad();
	  m_poThrustIndicator->renderQuad();
      
//      sprintf(strFont,"Velocity: %.1f", m_pPlayerShip->m_fVel);
//      m_poFont->print(strFont, CVector2(420.0f, 210.0f), 5.0f);
      
//      sprintf(strFont,"Thrust: %.1f", m_pPlayerShip->m_fThrust);
//      m_poFont->print(strFont, CVector2(420.0f, 560.0f), 5.0f);
      
      // Calc FPS
      unsigned long iTime = SDL_GetTicks();
      unsigned long iFPS = 0;
      if (iTime != m_iLastTime) {
         iFPS = 1000/(iTime - m_iLastTime);
      }
      sprintf(strFont,"%3ld FPS", iFPS);
//      m_poFont->print(strFont, CVector2(900.0f, 20.0f), 5.0f);
      m_iLastTime = iTime;
      
      glDisable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
      
//      glPopMatrix();
//      glMatrixMode(GL_MODELVIEW);
//      glPopMatrix();
   }


   //**************************************************************************************
   // Function name    : CHud::init
   // Author           : Gary Ingram
   // Return type      : void 
   // Date Created     : 25/05/2003
   // Description      : Initialises the hud. Loads all the textures (quite a few)  
   //**************************************************************************************
   void CHud::init()
   {
      CRGBAColour oDiffuse = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
	  CRGBAColour oAmbient = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
	  CRGBAColour oEmissive = CRGBAColour(1.0f,1.0f,1.0f,1.0f);

	  m_poFrontShield = new CShield();
	  m_poRearShield = new CShield();
	  m_poRightShield = new CShield();
	  m_poLeftShield = new CShield();
	  m_poSpeedIndicator = new CSpeedIndicator;
	  m_poThrustIndicator = new CThrustIndicator;

	  m_poFrontShield->init2D(0.3f, 0.3f, 0.25f, 0.1f, "Hud/hud_fore.png");
	  m_poFrontShield->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
	  m_poRearShield->init2D(0.3f, 0.7f, 0.25f, 0.1f, "Hud/hud_aft.png");
	  m_poRearShield->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
	  m_poRightShield->init2D(0.3f, 0.2f, 0.1f, 0.25f, "Hud/hud_right.png");
	  m_poRightShield->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
	  m_poLeftShield->init2D(0.7f, 0.2f, 0.1f, 0.25f, "Hud/hud_left.png");
	  m_poLeftShield->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
	  m_poSpeedIndicator->init2D(0.3f, 0.25f, 0.25f, 0.1f, "Hud/hud_speed.png");
	  m_poSpeedIndicator->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
	  m_poThrustIndicator->init2D(0.3f, 0.75f, 0.25f, 0.1f, "Hud/hud_thrust.png");
	  m_poThrustIndicator->setActiveMaterial(oDiffuse, oAmbient, oEmissive);

	  m_poSpeedIndicator->setTexturePercentage(0.1f);
	  m_poThrustIndicator->setTexturePercentage(0.1f);

      m_poFont = new CGLFont;
      m_poFont->load();
      
	  m_auiOffScreenTexture = g_oTextureManager.create(128,128);	  
//      m_auiTextures[6] = g_oTextureManager.load("Hud/hud_target.png");
//      m_auiTextures[7] = g_oTextureManager.create(128,128);
//      m_auiTextures[8] = g_oTextureManager.load("Hud/hud_reticle.png");
//      for (int i=0; i<9; i++) 
//      {
//         g_oTextureManager.texture(m_auiTextures[i])->init();
//      }
      
      // Set material
      m_oMaterial.m_oDiffuse = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
      m_oMaterial.m_oAmbient = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
      m_oMaterial.m_oEmissive = CRGBAColour(1.0f,1.0f,1.0f,1.0f);
      m_oMaterial.init();
      
      // Setup light
      CRGBAColour oLightAmbient(1.0f, 1.0f, 1.0f, 1.0f);
      CRGBAColour oLightDiffuse(1.0f, 1.0f, 1.0f, 1.0f);
      CVector3 oPosition(1000.0f, 1000.0f, -1000.0f);
      m_oLight.init(oLightAmbient, oLightDiffuse, oPosition);

//      m_po2DObject = new C2DObject;
   }

   void CHud::renderOffScreen()
   {
      // Perform offscreen rendering
      CTexture* pTexture = g_oTextureManager.texture(m_auiOffScreenTexture);
      pTexture->preRenderToTexture();
      // Clear screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      // Calculate direction vector
      CVector3 vecTarget = m_pTarget->m_ppMasses[0]->m_vecPos - m_pPlayerShip->m_ppMasses[0]->m_vecPos;
      float fRange = vecTarget.length();
      float fSize = m_pTarget->m_oModel.boundingSphere().m_fRadius;
      
      // Set Projection Matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      //gluPerspective(fAngle,1.0f,fRange-fSize, fRange+fSize);
      glOrtho(-fSize,fSize,-fSize,fSize,fRange-fSize,fRange+fSize);
      
      // Set Modelview Matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      m_oLight.enable();
      m_oLight.render();
      gluLookAt(m_pPlayerShip->m_ppMasses[0]->m_vecPos.X(), 
                m_pPlayerShip->m_ppMasses[0]->m_vecPos.Y(), 
                m_pPlayerShip->m_ppMasses[0]->m_vecPos.Z(),
                m_pTarget->m_ppMasses[0]->m_vecPos.X(), 
                m_pTarget->m_ppMasses[0]->m_vecPos.Y(), 
                m_pTarget->m_ppMasses[0]->m_vecPos.Z(),
                m_pPlayerShip->m_vecUp.X() - m_pPlayerShip->m_ppMasses[0]->m_vecPos.X(),
                m_pPlayerShip->m_vecUp.Y() - m_pPlayerShip->m_ppMasses[0]->m_vecPos.Y(),
                m_pPlayerShip->m_vecUp.Z() - m_pPlayerShip->m_ppMasses[0]->m_vecPos.Z());
      
      // Draw
      glDisable(GL_TEXTURE_2D);
      glShadeModel(GL_FLAT);
      m_pTarget->draw(false);
      m_oLight.disable();
      glShadeModel(GL_SMOOTH);
      glEnable(GL_TEXTURE_2D);
      // Finish up
      pTexture->postRenderToTexture(GL_LUMINANCE_ALPHA);
   }
   
//}
