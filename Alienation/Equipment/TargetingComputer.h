// TargetingComputer.h: interface for the CTargetingComputer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SDS_TARGETINGCOMPUTER_H
#define SDS_TARGETINGCOMPUTER_H

class CTargetingComputer;

#include "Equipment/Equipment.h"
#include "Game/Ship.h"
#include "3D/Light.h"

class CTargetingComputer : public CEquipment
{
 public:
   
   CTargetingComputer(CShip* pPlayerShip);
   
   virtual ~CTargetingComputer();
         
   void init();

   void render();
   
   void renderOffScreen();

   /**
    * Set the current target object.
    * @param poTarget The current target
    */
   void setTarget(CGameObject *poTarget)
   { m_pTarget = poTarget; }
   
 private:
   
   /**
    * The player's ship.
    */
   CShip* m_pPlayerShip;      

   /**
    * The current target.
    */
   CGameObject* m_pTarget;
   
   /**
    * Texture IDs
    */
   unsigned int m_auiOffScreenTexture;

   /** 
    * Reticle
    */
   CFrame* m_poTargetingReticle;

   /**
    * Font for drawing
    */
   CGLFont  *m_poFont;

   /**
    * Light for radar display
    */
   CLight m_oLight;
  
};

#endif //SDS_TARGETINGCOMPUTER_H
