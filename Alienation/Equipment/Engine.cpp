// Engine.cpp: implementation of the CEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/Engine.h"
#include "IO/Lua.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEngine::CEngine()
{

}

CEngine::~CEngine()
{

}

CEngine* CEngine::load(const char* strFileName) 
{
   // Make filename
   char pcFilename[255] = "Data/Scripts/";
   strcat(pcFilename,strFileName);
   
   // Init Lua interpreter
   NSDIO::CLua state(pcFilename);
   
   // Push engine table
   if (!state.setGlobalTable("engine")) {
      fprintf(stderr,"Can't find engine table in file: %s",pcFilename);
      return NULL;
   }

   // Create engine object
   CEngine* pEngine = new CEngine;

   // Get thrust data
   float fThrust(state.getNumber("thrust"));

   // Load flare information
   state.push("flare");
   const char* strFlareTex = state.getString("texture");
   CRGBAColour oFlareCol = state.getColour("colour");
   float fFlareSize = state.getNumber("maxsize");
   // Set flare information
   
   // Done with flare
   state.pop();

   // Load trail type
   state.push("trail");
   const char* strTrailType = state.getString("type");

   // If this is a particle trail
   if (strcmp(strTrailType,"particle") == 0) {

      // Get data from Lua file
      const char* strTrailTex = state.getString("texture");
      CRGBAColour oTrailCol = state.getColour("colour");
      float fTrailSize = state.getNumber("maxsize");
      int iNumParticles = static_cast<int>(state.getNumber("number"));

      // Set trail information
      

   }
   else {
      // Shouldn't get here at the moment
      fprintf(stderr,"AARGH - bit of a mistake there!\n");
      return NULL;
   }
   // Done with trails
   state.pop();

   // Done
   return pEngine;
}
