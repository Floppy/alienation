#include "2D/Hud.h"
#include "3D/TextureManager.h"
#include <SDL.h>
#include <SDL_opengl.h>

namespace NSD2D {

   CHud::CHud(CShip* pPlayerShip) :
      m_pPlayerShip(pPlayerShip),
      m_pTarget(NULL),
      m_iLastTime(SDL_GetTicks())
   {
      for (int i=0; i<8; i++) {
         m_auiTextures[i] = 0;
      }
      init();
   }
   
   CHud::~CHud()
   {
      for (int i=0; i<8; i++) {
         g_oTextureManager.removeReference(m_auiTextures[i]);
      }
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
      
      if (m_pPlayerShip->m_poShips[0].m_fVel == 0.0f)
      {
         fWidthSpeed = 0.001f;
      }
      else
      {
         fWidthSpeed = (m_pPlayerShip->m_poShips[0].m_fVel / fMaxSpeed) + 0.001f;
      }
      
      if (m_pPlayerShip->m_poShips[0].m_fThrust == 0.0f)
      {
         fWidthThrust = 0.001f;
      }
      else
      {
         fWidthThrust = (m_pPlayerShip->m_poShips[0].m_fThrust / fMaxThrust) + 0.001f;
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
      
      glPushMatrix();
      glLoadIdentity();
      glMatrixMode(GL_PROJECTION);
      glPushMatrix();
      glLoadIdentity();
      glOrtho(0.0f, 1024.0f, 768.0f, 0.0f, -1.0f, 1.0f);
      
      //////////////////////////////////////////////
      //Texture and blending stuff manually sets  //
      //the material properties. Hard coded,      //
      //shouldnt be really                        //
      //////////////////////////////////////////////

      glEnable(GL_BLEND);
      glDisable(GL_DEPTH_TEST);
      glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
      m_oMaterial.render();
      
      //////////////////////////////////////////////
      //Right Shield                              //
      //////////////////////////////////////////////
      
      avecTex[0] = CVector2( 0.0f, 1.0f);
      avecTex[1] = CVector2( 1.0f, 1.0f);
      avecTex[2] = CVector2( 1.0f, 0.0f);
      avecTex[3] = CVector2( 0.0f, 0.0f);
      
      g_oTextureManager.render(m_auiTextures[6]);
      m_po2DObject->renderQuad(0.0f, 500.0f, 400.0f, 500.0f, avecTex);
            
      g_oTextureManager.render(m_auiTextures[2]);
      m_po2DObject->renderQuad(540.0f, 480.0f, 150.0f, 200.0f, avecTex);
      
      //////////////////////////////////////////////
      //Left Shield                               //
      //////////////////////////////////////////////
            
      g_oTextureManager.render(m_auiTextures[3]);
      m_po2DObject->renderQuad(340.0f, 480.0f, 150.0f, 200.0f, avecTex);
      
      //////////////////////////////////////////////
      //Front Shield                              //
      //////////////////////////////////////////////
      
      g_oTextureManager.render(m_auiTextures[1]);
      m_po2DObject->renderQuad(415.0f, 560.0f, 200.0f, 150.0f, avecTex);
      
      //////////////////////////////////////////////
      //Back Shield                               //
      //////////////////////////////////////////////
      
      g_oTextureManager.render(m_auiTextures[0]);
      m_po2DObject->renderQuad(415.0f, 350.0f, 200.0f, 150.0f, avecTex);
      
      //////////////////////////////////////////////
      //Target Data                               //
      //////////////////////////////////////////////

      if (m_pTarget) {
         // Set quad
         avecTex[0] = CVector2( 0.0f, 0.0f);
         avecTex[1] = CVector2( 1.0f, 0.0f);
         avecTex[2] = CVector2( 1.0f, 1.0f);
         avecTex[3] = CVector2( 0.0f, 1.0f);
         // Calculate range
         CVector3 vecTarget = m_pTarget->m_ppMasses[0]->m_vecPos - m_pPlayerShip->m_ppMasses[0]->m_vecPos;
         int iRange = static_cast<int>(vecTarget.length());           
         // Range
         sprintf(strFont,"%5d m", iRange);
         m_poFont->print("Range:", CVector2(50.0f, 220.0f), 5.0f);
         m_poFont->print(strFont, CVector2(50.0f, 240.0f), 5.0f);
         // Velocity
         sprintf(strFont,"%5d m/s", static_cast<int>(m_pTarget->m_poShips[0].m_fVel));
         m_poFont->print("Velocity:", CVector2(50.0f, 260.0f), 5.0f);
         m_poFont->print(strFont, CVector2(50.0f, 280.0f), 5.0f);
         // Radar image
         g_oTextureManager.render(m_auiTextures[7]);
         m_po2DObject->renderQuad(37.0f, 180.0f, 135.0f, 135.0f, avecTex);
      }
      
      //////////////////////////////////////////////
      //Speed Bar                                 //
      //////////////////////////////////////////////
      
      avecTex[0] = CVector2( 0.0f, 1.0f);
      avecTex[1] = CVector2( fWidthSpeed - 0.001f, 1.0f);
      avecTex[2] = CVector2( fWidthSpeed - 0.001f, 0.0f);
      avecTex[3] = CVector2( 0.0f, 0.0f);
      
      g_oTextureManager.render(m_auiTextures[4]);
      m_po2DObject->renderQuad(415.0f, 420.0f, 200.0f * fWidthSpeed, 200.0f, avecTex);

      //////////////////////////////////////////////
      //Thrust Bar                                //
      //////////////////////////////////////////////
      
      avecTex[0] = CVector2( 0.0f, 1.0f);
      avecTex[1] = CVector2( fWidthThrust - 0.001f, 1.0f);
      avecTex[2] = CVector2( fWidthThrust - 0.001f, 0.0f);
      avecTex[3] = CVector2( 0.0f, 0.0f);
      
      g_oTextureManager.render(m_auiTextures[5]);
      m_po2DObject->renderQuad(415.0f, 550.0f, 200.0f * fWidthThrust, 200.0f, avecTex);
      
      sprintf(strFont,"Velocity: %.1f", m_pPlayerShip->m_poShips[0].m_fVel);
      m_poFont->print(strFont, CVector2(420.0f, 210.0f), 5.0f);
      
      sprintf(strFont,"Thrust: %.1f", m_pPlayerShip->m_poShips[0].m_fThrust);
      m_poFont->print(strFont, CVector2(420.0f, 560.0f), 5.0f);
      
      // Calc FPS
      unsigned long iTime = SDL_GetTicks();
      unsigned long iFPS = 0;
      if (iTime != m_iLastTime) {
         iFPS = 1000/(iTime - m_iLastTime);
      }
      sprintf(strFont,"%3ld FPS", iFPS);
      m_poFont->print(strFont, CVector2(900.0f, 20.0f), 5.0f);
      m_iLastTime = iTime;
      
      glDisable(GL_BLEND);
      glEnable(GL_DEPTH_TEST);
      
      glPopMatrix();
      glMatrixMode(GL_MODELVIEW);
      glPopMatrix();
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
      m_poFont = new CGLFont;
      m_poFont->load();
      
      m_auiTextures[0] = g_oTextureManager.load("Hud/hud_fore.png");
      m_auiTextures[1] = g_oTextureManager.load("Hud/hud_aft.png");
      m_auiTextures[2] = g_oTextureManager.load("Hud/hud_right.png");
      m_auiTextures[3] = g_oTextureManager.load("Hud/hud_left.png");
      m_auiTextures[4] = g_oTextureManager.load("Hud/hud_speed.png");
      m_auiTextures[5] = g_oTextureManager.load("Hud/hud_thrust.png");
      m_auiTextures[6] = g_oTextureManager.load("Hud/hud_target.png");
      m_auiTextures[7] = g_oTextureManager.create(128,128);
      for (int i=0; i<8; i++) 
      {
         g_oTextureManager.texture(m_auiTextures[i])->init();
      }
      
      // Set material
      m_oMaterial.m_oDiffuse = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
      m_oMaterial.m_oAmbient = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
      m_oMaterial.m_oEmissive = CRGBAColour(1.0f,1.0f,1.0f,0.9f);
      m_oMaterial.init();
      
      m_po2DObject = new C2DObject;
   }

   void CHud::renderOffScreen()
   {
      // Perform offscreen rendering
      CTexture* pTexture(g_oTextureManager.texture(m_auiTextures[7]));
      pTexture->preRenderToTexture();
      // Clear screen
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
      
      // Calculate direction vector
      CVector3 vecTarget = m_pTarget->m_ppMasses[0]->m_vecPos - m_pPlayerShip->m_ppMasses[0]->m_vecPos;
      float fRange = vecTarget.length();
      float fSize = m_pTarget->m_poShips[0].m_oModel.boundingRadius() * 1.1;
      float fAngle = RAD_TO_DEG(atan(fSize / fRange) * 2);
      
      // Set Projection Matrix
      glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluPerspective(fAngle,1.0f,fRange-fSize, fRange+fSize);
      
      // Set Modelview Matrix
      glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();
      gluLookAt(m_pPlayerShip->m_ppMasses[0]->m_vecPos.X(), 
                m_pPlayerShip->m_ppMasses[0]->m_vecPos.Y(), 
                m_pPlayerShip->m_ppMasses[0]->m_vecPos.Z(),
                m_pTarget->m_ppMasses[0]->m_vecPos.X(), 
                m_pTarget->m_ppMasses[0]->m_vecPos.Y(), 
                m_pTarget->m_ppMasses[0]->m_vecPos.Z(),
                m_pPlayerShip->m_poShips[0].m_vecUp.X() - m_pPlayerShip->m_ppMasses[0]->m_vecPos.X(),
                m_pPlayerShip->m_poShips[0].m_vecUp.Y() - m_pPlayerShip->m_ppMasses[0]->m_vecPos.Y(),
                m_pPlayerShip->m_poShips[0].m_vecUp.Z() - m_pPlayerShip->m_ppMasses[0]->m_vecPos.Z());
      
      // Draw
      m_pTarget->draw(false);
      // Finish up
      pTexture->postRenderToTexture(GL_LUMINANCE);
   }
   
}
