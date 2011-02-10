// Engine.cpp: implementation of the CEngine class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/Engine.h"
#include "IO/Lua.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEngine::CEngine() :
   m_fCurrentThrust(0.0f),
   m_fMaxThrust(0.0f)
{

}

CEngine::~CEngine()
{

}

void CEngine::drawBlended() const {
   if (m_fCurrentThrust > 0.0f)
      m_oTrail.render();
}

void CEngine::setFlare(const char* strTexture, CRGBAColour oCol, float fSize) {
   m_oTrail.setFlare(strTexture, oCol, fSize);   
}

void CEngine::setTrail(const char* strTexture, CRGBAColour oCol, float fSize, int iNumParticles) {
   m_oTrail.setup(iNumParticles,CVector3(0,0,0));
   m_oTrail.setTrail(strTexture, oCol, fSize);
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
   pEngine->setMaxThrust(fThrust);

   // Load flare information
   state.push("flare");
   const char* strFlareTex = state.getString("texture");
   CRGBAColour oFlareCol = state.getColour("colour");
   float fFlareSize = state.getNumber("maxsize");
   // Set flare information
   pEngine->setFlare(strFlareTex,oFlareCol,fFlareSize);
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
      pEngine->setTrail(strTrailTex,oTrailCol,fTrailSize,iNumParticles);

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

void CEngine::update(float fDT, CVector3 vecPos, CVector3 vecStart, 
                     CVector3 vecDistance, CVector3 vecUp, CVector3 vecRight) {

   m_oTrail.update(fDT,m_fCurrentThrust,vecPos,vecStart,vecDistance,vecUp,vecRight,1.5f, 0.5f);
   
}

