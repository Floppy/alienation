// Engine.h: interface for the CEngine class.
//
//////////////////////////////////////////////////////////////////////

#ifndef SDS_ENGINE_H
#define SDS_ENGINE_H

#include "Equipment/Equipment.h"
#include "Equipment/Trail.h"

using namespace std;

class CEngine : public CEquipment  
{
public:

   CEngine();
   
   virtual ~CEngine();   

   /**
    * Load a engine object from a Lua file.
    * @param strFileName The Lua file to load from.
    * @param type The engine type to create.
    * @return A pointer to a new engine object
    */
   static CEngine* load(const char* strFileName);

   /**
    * Set thrust percentage.
    * @param fThrust The current thrust value, between 0 and 1.
    */
   void setThrust(float fThrust) 
   { m_fCurrentThrust = fThrust * m_fMaxThrust; }

   /**
    * Get thrust value.
    * @return The thrust put out by this engine, in newtons.
    */
   float getThrust() const
   { return m_fCurrentThrust; }
    
   /**
    * Set maximum thrust.
    * @param fThrust The maximum thrust value.
    */
   void setMaxThrust(float fThrust) 
   { m_fMaxThrust = fThrust; }

   /**
    * Get max thrust value.
    * @return The maximum thrust put out by this engine, in newtons.
    */
   float getMaxThrust() const
   { return m_fMaxThrust; }
    
   /**
    * Render blended 3D content.
    */
   void drawBlended() const;

   /**
    * Update any state information
    */
   void update(float fDT, CVector3 vecPos, CVector3 vecStart, 
               CVector3 vecDistance, CVector3 vecUp, CVector3 vecRight);

   /**
    * Initialise engine flare.
    */ 
   void setFlare(const char* strTexture, CRGBAColour oCol, float fSize);

   /** 
    * Initialise engine trail.
    */
   void setTrail(const char* strTexture, CRGBAColour oCol, float fSize, int iNumParticles);

private:

   /**
    * Trail.
    */
   CTrail m_oTrail;

   /**
    * Current thrust value.
    */ 
   float m_fCurrentThrust;

   /** 
    * Maximum thrust value.
    */
   float m_fMaxThrust;

};

#endif // SDS_ENGINE_H
