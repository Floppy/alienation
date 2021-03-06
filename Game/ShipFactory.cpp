#include "Game/ShipFactory.h"
#include "Game/PlayerShip.h"
#include "IO/Lua.h"
#include "AI/AIShip.h"
#include "Math/Random.h"
#include <string.h>

//namespace NSDIO {

   using namespace NSDIO;

   CShip* CShipFactory::load(const char *strFileName, bool bPlayer) {
	  
      unsigned int i;      
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
      for (i=0; i<iNumWeapons; i++) {
         pWeapons[i] = state.getVector3(i);
      }
      pShip->setWeapons(iNumWeapons,pWeapons,strWeapon);
      delete [] pWeapons;
      state.pop();

      // Load engines
      const char* strEngine = state.getString("enginetype");
      state.push("engines");
      unsigned int iNumEngines = state.tableSize();
      CVector3* pEngines = new CVector3[iNumEngines];
      for (i=0; i<iNumEngines; i++) {
         pEngines[i] = state.getVector3(i);
      }
      pShip->setEngines(iNumEngines,pEngines,strEngine);
      delete [] pEngines;
      state.pop();

      // Load brakes
      state.push("brakes");
      unsigned int iNumBrakes = state.tableSize();
      CVector3* pBrakes = new CVector3[iNumBrakes];
      for (i=0; i<iNumBrakes; i++) {
         pBrakes[i] = state.getVector3(i);
      } 
      pShip->setBrakes(iNumBrakes,pBrakes);
      delete [] pBrakes;
      state.pop();

      // Setup performance stats
      float fPitch = state.getNumber("pitch");
      float fYaw = state.getNumber("yaw");
      float fRoll = state.getNumber("roll");
      pShip->setPerformance(fPitch,fYaw,fRoll);
      
      // Add front shield
      const char* strShield = state.getString("shield_fore");
      CShield* pShield = CShield::load(strShield,SHIELD_FORE);
      if (pShield)
	pShip->m_lShields.push_back(pShield);

      // Add rear shield
      strShield = state.getString("shield_aft");
      pShield = CShield::load(strShield,SHIELD_AFT);
      if (pShield)
	pShip->m_lShields.push_back(pShield);

      // Add right shield
      strShield = state.getString("shield_right");
      pShield = CShield::load(strShield,SHIELD_RIGHT);
      if (pShield)
	pShip->m_lShields.push_back(pShield);

      // Add left shield
      strShield = state.getString("shield_left");
      pShield = CShield::load(strShield,SHIELD_LEFT);
      if (pShield)
	pShip->m_lShields.push_back(pShield);
      

      CRGBAColour oDiffuse = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
      CRGBAColour oAmbient = CRGBAColour(0.0f,0.0f,0.0f,1.0f);
      CRGBAColour oEmissive = CRGBAColour(1.0f,1.0f,1.0f,1.0f);


      // Add speed indicator
      CSpeedIndicator* pSpeed = new CSpeedIndicator;
      pSpeed->init2D(0.375f, 0.27f, 0.25f, 0.042f, "Hud/hud_speed.png");
      pSpeed->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
      pSpeed->setTexturePercentage(0.1f);
      pShip->m_poSpeedIndicator = pSpeed;

      // Add thrust indicator
      CThrustIndicator* pThrust = new CThrustIndicator;
      pThrust->init2D(0.375f, 0.69f, 0.25f, 0.042f, "Hud/hud_thrust.png");
      pThrust->setActiveMaterial(oDiffuse, oAmbient, oEmissive);
      pThrust->setTexturePercentage(0.1f);
      pShip->m_poThrustIndicator = pThrust;

      // Add targeting computer
      CTargetingComputer* pTargetComp = new CTargetingComputer(pShip);
      pTargetComp->init();
      pShip->m_poTargetingComputer = pTargetComp;

      return pShip;
   }
   
//}
