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
      CRGBAColour oDiffuse = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
      CRGBAColour oAmbient = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
      CRGBAColour oEmissive = CRGBAColour(1.0f,1.0f,1.0f,1.0f);



   m_poTargetingReticle = new CFrame;
   
   m_poTargetingReticle->init2D(0.0f, 0.1f, 0.0f, 0.1f, "Hud/hud_reticle.png");
   m_poTargetingReticle->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
   
   m_poFont = new CGLFont;
   m_poFont->load();
   
   m_auiOffScreenTexture = g_oTextureManager.create(128,128);	  
   //m_auiTextures[6] = g_oTextureManager.load("Hud/hud_target.png");

}

void CTargetingComputer::render() 
{
      
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
         // Calculate range
	 //NSDMath::CVector3 vecTarget = m_pTarget->m_ppMasses[0]->m_vecPos - m_pPlayerShip->m_ppMasses[0]->m_vecPos;
         //int iRange = static_cast<int>(vecTarget.length());           
         // Range
         //sprintf(strFont,"%5d m", iRange);
         //m_poFont->print("Range:", CVector2(50.0f, 220.0f), 5.0f);
         //m_poFont->print(strFont, CVector2(50.0f, 240.0f), 5.0f);
         // Velocity
         //sprintf(strFont,"%5d m/s", static_cast<int>(m_pTarget->m_fVel));
         //m_poFont->print("Velocity:", CVector2(50.0f, 260.0f), 5.0f);
         //m_poFont->print(strFont, CVector2(50.0f, 280.0f), 5.0f);
         // Radar image
         //g_oTextureManager.render(m_auiTextures[7]);
         //m_po2DObject->renderQuad(37.0f, 180.0f, 135.0f, 135.0f, avecTex);
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
      glShadeModel(GL_FLAT);
      m_pTarget->draw(false);
      glShadeModel(GL_SMOOTH);
      glEnable(GL_TEXTURE_2D);
      // Finish up
      pTexture->postRenderToTexture(GL_LUMINANCE_ALPHA);
   }
