// TargetingComputer.cpp: implementation of the CTargetingComputer class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/TargetingComputer.h"
#include "3D/TextureManager.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTargetingComputer::CTargetingComputer(CShip* pPlayerShip) :
   m_pPlayerShip(pPlayerShip),
   m_pTarget(NULL)
{

}

CTargetingComputer::~CTargetingComputer()
{
   g_oTextureManager.removeReference(m_auiOffScreenTexture);

}

void CTargetingComputer::init()
{
   // Create material colours
   CRGBAColour oDiffuse = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
   CRGBAColour oAmbient = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
   CRGBAColour oEmissive = CRGBAColour(1.0f,1.0f,1.0f,1.0f);

   // Create targeting reticle
   m_poTargetingReticle = new CFrame;
   m_poTargetingReticle->init2D(0.0f, 0.0f, 0.1f, 0.1f, "Hud/hud_reticle.png");
   m_poTargetingReticle->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
   
   m_poFont = g_oFontManager.getFont(1);
   
   // Create offscreen texture
   m_auiOffScreenTexture = g_oTextureManager.create(128,128);

   // Change to green colour
   oEmissive = CRGBAColour(0.0f,1.0f,0.0f,1.0f);

   // Setup main frame
   init2D(0.0f, 0.0f, 0.175f, 0.6f,"Hud/hud_target.png");
   setActiveMaterial(oDiffuse, oAmbient, oEmissive);

   // Change to slightly transparent green colour
   oDiffuse = CRGBAColour(0.0f,0.0f,0.0f,0.5f);
   oAmbient = CRGBAColour(0.0f,0.0f,0.0f,0.5f);
   oEmissive = CRGBAColour(0.0f,1.0f,0.0f,0.5f);

   // Create holo target 
   m_poHoloTarget = new CFrame;
   m_poHoloTarget->init2D(0.015f, 0.02f, 0.145f, 0.1933f,"");
   m_poHoloTarget->setActiveMaterial(oDiffuse, oAmbient, oEmissive, m_auiOffScreenTexture);
      
}

void CTargetingComputer::render() 
{
   // Display surround
   renderQuad();

   char strFont[256];

   if (m_pTarget) {
      // Calculate position of targeting reticle
      CVector3 pos = m_pTarget->m_ppMasses[0]->m_vecPos;
      // Get viewport
      int viewport[4];
      double modelview[16];
      double projection[16];
      glGetIntegerv(GL_VIEWPORT,viewport);
      glGetDoublev(GL_MODELVIEW_MATRIX,modelview);
      glGetDoublev(GL_PROJECTION_MATRIX,projection);
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
      // Rescale to 0..1
      dX /= viewport[2];
      dY /= viewport[3];
		double dW = 32.0f / viewport[2];
		double dH = 32.0f / viewport[3];
      // Render reticle
      m_poTargetingReticle->setPosition(dX-dW, (1-dY)-dH, dW*2, dH*2);
		m_poTargetingReticle->renderQuad();
		// Radar imagexs
		m_poHoloTarget->renderQuad();
         // Calculate range
		NSDMath::CVector3 vecTarget = m_pTarget->m_ppMasses[0]->m_vecPos - m_pPlayerShip->m_ppMasses[0]->m_vecPos;
      int iRange = static_cast<int>(vecTarget.length());           
      // Range
      sprintf(strFont,"%5d m", iRange);
      m_poFont->print("Range:", CVector2(0.03f, 0.25f), 0.0075f, CVector3(0,1,0));
      m_poFont->print(strFont, CVector2(0.03f, 0.28f), 0.0075f, CVector3(0,1,0));
      // Velocity
      sprintf(strFont,"%5d m/s", static_cast<int>(m_pTarget->m_fVel));
      g_oTextureManager.render(m_auiOffScreenTexture);
      //m_po2DObject->renderQuad(37.0f, 180.0f, 135.0f, 135.0f, avecTex);
      m_poFont->print("Velocity:", CVector2(0.03f, 0.32f), 0.0075f, CVector3(0,1,0));
      m_poFont->print(strFont, CVector2(0.03f, 0.35f), 0.0075f, CVector3(0,1,0));
    }
}
 
  void CTargetingComputer::renderOffScreen()
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
      m_pTarget->draw(false);
      glEnable(GL_TEXTURE_2D);
      // Finish up
      pTexture->postRenderToTexture(GL_RGBA);
   }
