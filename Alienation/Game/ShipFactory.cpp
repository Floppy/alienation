#include "Game/ShipFactory.h"
#include "Game/PlayerShip.h"
#include "IO/Lua.h"
#include "AI/AIShip.h"
#include "Math/Random.h"
#include <string.h>

//namespace NSDIO {

   using namespace NSDIO;

   CShip* CShipFactory::load(const char *strFileName, bool bPlayer) {
      
      // Make filename
      char pcFilename[255] = "Data/Scripts/";
      strcat(pcFilename,strFileName);
      
      // Init Lua interpreter
      CLua state(pcFilename);
     
      // Push table
      if (!state.setGlobalTable("ship")) {
         fprintf(stderr,"Can't find ship table in file: %s",pcFilename);
         return NULL;
      }
      
      // Get models
      const char* strModel = state.getString("model");
      const char* strCockpit = state.getString("cockpit");
      const char* strWeapon = state.getString("weapontype");

      // Get performance stats
      float fPitch = state.getNumber("pitch");
      float fYaw = state.getNumber("yaw");
      float fRoll = state.getNumber("roll");
      float fThrust = state.getNumber("thrust");
      float fMass = state.getNumber("mass");

      // Create a new ship
      CShip* pShip = bPlayer ? 
         static_cast<CShip*>(new CPlayerShip(fMass)) : 
         static_cast<CShip*>(new CAIShip(fMass));
                             
      // Load
      pShip->load(strModel, strCockpit);

      // Setup
      pShip->setPerformance(fPitch,fYaw,fRoll,fThrust);
      pShip->loadWeapon(strWeapon);
      
      return pShip;
   }
   
//}
