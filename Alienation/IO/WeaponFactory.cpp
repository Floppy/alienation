#include "IO/WeaponFactory.h"
#include "IO/Lua.h"
#include <string.h>

namespace NSDIO {

   CWeapon* CWeaponFactory::load(const char *strFileName) {
      
      // Make filename
      char pcFilename[255] = "Data/Scripts/";
      strcat(pcFilename,strFileName);
      
      // Init Lua interpreter
      CLua state(pcFilename);
     
      // Push table
      if (!state.setGlobalTable("weapon")) {
         fprintf(stderr,"Can't find weapon table in file: %s",pcFilename);
         return NULL;
      }

      // Get position - this is fixed for now, should really be set in the ship loader
      CVector3 vecPosition(0.0f, -0.3f, -3.3f);
      
      // Get stats
      float fSize = state.getFloat("size");
      float fLifetime = state.getFloat("lifetime");
      float fSpeed = state.getFloat("speed");
      float fRate = state.getFloat("firerate");
      
      // Get sound effect info
      const char* strSound = state.getString("sound");

      // Get material info
      const char* strTexture = state.getString("texture");
      CRGBAColour oColour(state.getColour("colour"));

      // Return a new weapon
      return new CWeapon(vecPosition,fSize,fLifetime,fSpeed,fRate,strSound,strTexture,oColour);
   }
   
}