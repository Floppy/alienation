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
    */
   CHud();

   /**
    * Destructor.
    */
   virtual ~CHud();
        
   /**
    * Initialises the hud. 
    * Loads all the textures (quite a few)  
    */
   void init();
   
   /**
    * Draw to screen.
    * Draws the ship hud including all the information relevent to 
    * the player ship. Will be enlarged over time to include 
    * more ship information. Note: information regarding the 
    * ships target will be drawn in the DrawHoloTarget routine.
    * @param fSpeed Current speed value
    * @param fMaxSpeed Maximum speed value
    * @param fThrust Current thrust value
    * @param fMaxThrust Maximum thrust value
    */
   void draw(float fSpeed, float fMaxSpeed, float fThrust, float fMaxThrust);
   
   /**
    * Draw a "hologram" of the current target into the radar display.
    * This routine draws the hologram on the target on the hud. 
    * Although this is its main function it is also used to 
    * display other target information  
    * @param poTarget The current target
    * @param poMass not sure what this is, sorry!
    * @param poThisShip The player's ship
    * @bug (doc) Don't knot what poMass represents.
    */
   void drawTargetData(CShipData *poTarget, CMass **poMass, CShip *poThisShip);

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
   unsigned int m_auiTextures[7];

   /**
    * Object for 2d drawing
    */
   C2DObject *m_po2DObject;
};

#endif // HUD_H
