#include "IO/Lua.h"

#include <string.h>

extern "C" {
#include <lauxlib.h>
}

namespace NSDIO {

   using namespace NSDMath;

   int panic(lua_State *state) {
      // Print error message
      fprintf(stderr,"-------------------------\n");
      fprintf(stderr,"ERROR in Lua interpreter!\n");
      fprintf(stderr,"-------------------------\n");
      // Get debugging info
      lua_Debug debug;
      if (lua_getstack(state, 0, &debug) && lua_getinfo(state, "S", &debug)) {
          // Print information
          fprintf(stderr,"name: %s\n", debug.name);
          fprintf(stderr,"namewhat: %s\n", debug.namewhat);
          fprintf(stderr,"source: %s\n", debug.short_src);
          fprintf(stderr,"what: %s\n", debug.what);
          fprintf(stderr,"line: %d\n", debug.currentline);
          fprintf(stderr,"nups: %d\n", debug.nups);
      }
      // Done
      return 1;
   }

   CLua::CLua(const char* filename) :
      m_pState(NULL)
   {
      // Open Lua
      m_pState = lua_open();
      // Set panic function      
      lua_atpanic(m_pState,panic);
      // Run file
      lua_dofile(m_pState,filename);
   }

   CLua::~CLua() 
   {
      lua_close(m_pState);
   }

   bool CLua::setGlobalTable(const char* table)
   {
      lua_getglobal(m_pState,table);
      if (!lua_istable(m_pState,-1)) {
         return false;
      }
      return true;
   }

   bool CLua::enterTable(const char* table) {
      lua_pushstring(m_pState, table);
      lua_gettable(m_pState,-2);
      if (!lua_istable(m_pState,-1))
         return false;
      return true;      
   }
   
   void CLua::exitTable() {
      lua_pop(m_pState,1);
   }

   float CLua::getNumber(const char* field)
   {
      lua_pushstring(m_pState, field);
      lua_gettable(m_pState,-2);
      if (!lua_isnumber(m_pState,-1)) {
         return 0;
      }
      // Get number
      float fResult = static_cast<float>(lua_tonumber(m_pState,-1));
      // Pop stack
      lua_pop(m_pState,1);
      // Done
      return fResult;
   }
   
   const char* CLua::getString(const char* field)
   {
      lua_pushstring(m_pState, field);
      lua_gettable(m_pState,-2);
      if (!lua_isstring(m_pState,-1)) {
         return NULL;
      }
      // Copy out string
      const char* strTemp = lua_tostring(m_pState,-1);
      char* strResult = new char[strlen(strTemp)+1];
      strcpy(strResult,strTemp);
      // Pop stack
      lua_pop(m_pState,1);
      // Done
      return strResult;
   }

   CRGBAColour CLua::getColour(const char* field)
   {
      if (!enterTable(field))
         return CRGBAColour(0,0,0,0);
      // Get values
      float fRed = getNumber("r");
      float fGreen = getNumber("g");
      float fBlue = getNumber("b");
      float fAlpha = getNumber("a");
      // Pop stack
      exitTable();
      // Done
      return CRGBAColour(fRed,fGreen,fBlue,fAlpha);
   }

   CVector3 CLua::getVector3(const char* field) 
   {
      if (!enterTable(field))
         return CVector3(0,0,0);
      // Get values
      float fX = getNumber("x");
      float fY = getNumber("y");
      float fZ = getNumber("z");
      // Pop stack
      exitTable();
      // Done
      return CVector3(fX,fY,fZ);
   }

   CVector2 CLua::getVector2(const char* field) 
   {
      if (!enterTable(field))
         return CVector2(0,0);
      // Get values
      float fX = getNumber("x");
      float fY = getNumber("y");
      // Pop stack
      exitTable();
      // Done
      return CVector2(fX,fY);
   }

}
