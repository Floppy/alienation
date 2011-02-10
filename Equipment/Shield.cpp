// Shield.cpp: implementation of the CShield class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/Shield.h"
#include "IO/Lua.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShield::CShield()
{

}

CShield::~CShield()
{

}

int CShield::getShieldType()
{
   return m_iShieldType;
}

void CShield::setShieldType(int iType)
{
   m_iShieldType = iType;
}

CShield* CShield::load(const char* strFileName, shieldType type) 
{
   // Make filename
   char pcFilename[255] = "Data/Scripts/";
   strcat(pcFilename,strFileName);
   
   // Init Lua interpreter
   NSDIO::CLua state(pcFilename);
   
   // Push table
   if (!state.setGlobalTable("shield")) {
      fprintf(stderr,"Can't find shield table in file: %s",pcFilename);
      return NULL;
   }

   // Create shield object
   CShield* pShield = new CShield;

   // Set type
   pShield->setShieldType(type);

   // Load information from file.
   switch (type) {
   case SHIELD_FORE:
      // Load fore shield
      state.push("fore");
      break;
   case SHIELD_AFT:
      // Load fore shield
      state.push("aft");
      break;
   case SHIELD_RIGHT:
      // Load fore shield
      state.push("right");
      break;
   case SHIELD_LEFT:
      // Load fore shield
      state.push("left");
      break;
   default:
     break;
   }

   // Load HUD information
   state.push("hud");
   CVector2 oPos(state.getVector2("position"));
   CVector2 oSize(state.getVector2("size"));
   CRGBAColour oColour(state.getColour("colour"));
   const char* strTexture = state.getString("texture");
   state.pop();

   // Finish loading direction-specific data
   state.pop();

   // Setup shield
   pShield->init2D(oPos.X(), oPos.Y(), oSize.X(), oSize.Y(), strTexture);
   pShield->setActiveMaterial(oColour, oColour, oColour);
   
   // Done
   return pShield;
}
