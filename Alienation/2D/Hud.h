#ifndef HUD_H
#define HUD_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "GL/GLFont.h"
#include "Game/Ship.h"
#include "2D/2DObject.h"
#include "config.h"
#include "3D/Material.h"


/** 
 * Head-Up Display. 
 * Overlays a HUD on the screen, and display various bits of important information.
 */
class CHud
{
public:

   /**
    * Constructor.
    * @param poThisShip The player's ship
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
    * @param fSpeed Current speed value
    * @param fMaxSpeed Maximum speed value
    * @param fThrust Current thrust value
    * @param fMaxThrust Maximum thrust value
    */
   void render();//float fSpeed, float fMaxSpeed, float fThrust, float fMaxThrust);
   
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
   void setTarget(CShip *poTarget)
   { m_pTarget = poTarget; }

 protected:

   /**
    * Draw a quad onto the screen.
    * This draws a quad with texture co-ordinates. Should be in 
    * a utility class or what ever, which I think floppy is 
    * doing. Still, helped out for a while tho ;)  
    * @param Verts array of 4 vertices
    * @param Tex array of 4 texture coordinates
    */
   void drawQuad(CVector3 *Verts, CVector2 *Tex);

   /**
    * Draw 2D quad to screen
    * This routine draws a 2d quad on a orthonganal display  
    * @param fPosX X Position of quad
    * @param fPosY Y position of quad
    * @param fWidth Width of quad
    * @param fHeight Height of quad
    * @param Tex Array containing texure coordinates
    */
   void draw2DQuad(float fPosX, float fPosY, float fWidth, float fHeight, CVector2 *Tex);

   /**
    * The player's ship.
    */
   CShip* m_pPlayerShip;

   /**
    * The current target.
    */
   CShip* m_pTarget;

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
   unsigned int m_auiTextures[8];

   /**
    * Object for 2d drawing
    */
   C2DObject *m_po2DObject;
};

#endif // HUD_H
