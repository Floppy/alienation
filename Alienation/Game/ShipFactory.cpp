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
      
      // Create a new ship
      float fMass = state.getNumber("mass");
      CShip* pShip = bPlayer ? 
         static_cast<CShip*>(new CPlayerShip(fMass)) : 
         static_cast<CShip*>(new CAIShip(fMass));

      // Load models
      const char* strModel = state.getString("model");
      const char* strCockpit = state.getString("cockpit");
      pShip->load(strModel, strCockpit);

      // Load weapons
      const char* strWeapon = state.getString("weapontype");
      state.push("weapons");
      unsigned int iNumWeapons = state.tableSize();
      CVector3* pWeapons = new CVector3[iNumWeapons];
      for (unsigned int i=0; i<iNumWeapons; i++) {
         pWeapons[i] = state.getVector3(i);
      }
      pShip->setWeapons(iNumWeapons,pWeapons,strWeapon);
      delete [] pWeapons;
      state.pop();

      // Load trails
      state.push("trails");
      unsigned int iNumTrails = state.tableSize();
      CVector3* pTrails = new CVector3[iNumTrails];
      for (unsigned int i=0; i<iNumTrails; i++) {
         pTrails[i] = state.getVector3(i);
      }
      pShip->setTrails(iNumTrails,pTrails);
      delete [] pTrails;
      state.pop();

      // Load brakes
      state.push("brakes");
      unsigned int iNumBrakes = state.tableSize();
      CVector3* pBrakes = new CVector3[iNumBrakes];
      for (unsigned int i=0; i<iNumBrakes; i++) {
         pBrakes[i] = state.getVector3(i);
      }
      pShip->setBrakes(iNumBrakes,pBrakes);
      delete [] pBrakes;
      state.pop();

      // Setup performance stats
      float fPitch = state.getNumber("pitch");
      float fYaw = state.getNumber("yaw");
      float fRoll = state.getNumber("roll");
      float fThrust = state.getNumber("thrust");
      pShip->setPerformance(fPitch,fYaw,fRoll,fThrust);
      
      return pShip;
   }
   
//}
