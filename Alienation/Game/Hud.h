#ifndef HUD_H
#define HUD_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "2D/GLFont.h"
#include "Game/GameObject.h"
#include "Game/Ship.h"
#include "2D/2DObject.h"
#include "config.h"
#include "3D/Material.h"
#include "3D/Light.h"
#include "Equipment/Shield.h"
#include "Equipment/SpeedIndicator.h"
#include "Equipment/ThrustInformation.h"

namespace NSD2D {

   /** 
    * Head-Up Display. 
    * Overlays a HUD on the screen, and display various bits of important information.
    */
   class CHud
   {
   public:
      
      /**
       * Constructor.
       * @param pPlayerShip The player's ship
       */
      CHud(CShip *pPlayerShip);
      
      /**
       * Destructor.
       */
      virtual ~CHud();
      
      /**
       * Initialises the hud. 
       * Loads and initialises all the textures (quite a few).
       */
      void init();
      
      /**
       * Draw to screen.
       * Draws the ship hud including all the information relevent to 
       * the player ship. Will be enlarged over time to include 
       * more ship information.
       */
      void render();
      
      /**
       * Perform offscreen rendering.
       * This must be called before any other rendering is done, as it will 
       * destroy any existing information in the framebuffer.
       */
      void renderOffScreen();
      
      /**
       * Set the current target object.
       * @param poTarget The current target
       */
      void setTarget(CGameObject *poTarget)
      { m_pTarget = poTarget; }
      
   protected:
      
      /**
       * The player's ship.
       */
      CShip* m_pPlayerShip;
      
      /**
       * The current target.
       */
      CGameObject* m_pTarget;
      
      /**
       * Font for drawing
       */
      CGLFont  *m_poFont;
      
      /**
       * Time at last frame
       */
      unsigned long m_iLastTime;
      
      /**
       * Material info
       */
      CMaterial m_oMaterial;
      
      /**
       * Texture IDs
       */
      unsigned int m_auiOffScreenTexture;
      
      /**
       * Object for 2d drawing
       */
      C2DObject *m_po2DObject;

      /**
       * Light for radar display
       */
      CLight m_oLight;
  
   private:
	   CShield * m_poLeftShield;
	   CShield * m_poRightShield;
	   CShield * m_poRearShield;
	   CShield * m_poFrontShield;
	   CSpeedIndicator * m_poSpeedIndicator;
	   CThrustIndicator * m_poThrustIndicator;
   };
   
}

#endif // HUD_H
