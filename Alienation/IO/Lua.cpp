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

   bool CLua::push(const char* name, int type) {
      lua_pushstring(m_pState, name);
      lua_rawget(m_pState,-2);
      if (lua_type(m_pState,-1) != type) {
         fprintf(stderr,"ERROR: Wrong type! Expected %s, got %s\n",
                 lua_typename(m_pState,type),lua_typename(m_pState,lua_type(m_pState,-1)));
         pop();
         return false;
      }
      return true;      
   }

   bool CLua::push(unsigned int index, int type) {
      lua_rawgeti(m_pState,-1,index+1);
      if (lua_type(m_pState,-1) != type) {
         fprintf(stderr,"ERROR: Wrong type! Expected %s, got %s\n",
                 lua_typename(m_pState,type),lua_typename(m_pState,lua_type(m_pState,-1)));
         pop();
         return false;
      }
      return true;      
   }
   
   void CLua::pop() {
      lua_pop(m_pState,1);
   }

   unsigned int CLua::tableSize() {
      unsigned int iResult = luaL_getn(m_pState,-1);
      return iResult;
   }

   float CLua::getNumber(const char* field)
   {
      if (!push(field,LUA_TNUMBER))
         return 0;
      // Get number
      float fResult = static_cast<float>(lua_tonumber(m_pState,-1));
      // Pop stack
      pop();
      // Done
      return fResult;
   }
   
   const char* CLua::getString(const char* field)
   {
      if (!push(field,LUA_TSTRING))
         return NULL;
      // Copy out string
      const char* strTemp = lua_tostring(m_pState,-1);
      char* strResult = new char[strlen(strTemp)+1];
      strcpy(strResult,strTemp);
      // Pop stack
      pop();
      // Done
      return strResult;
   }

   CRGBAColour CLua::getColour(const char* field)
   {
      if (!push(field))
         return CRGBAColour(0,0,0,0);
      // Get values
      float fRed = getNumber("r");
      float fGreen = getNumber("g");
      float fBlue = getNumber("b");
      float fAlpha = getNumber("a");
      // Pop stack
      pop();
      // Done
      return CRGBAColour(fRed,fGreen,fBlue,fAlpha);
   }

   CVector3 CLua::getVector3(const char* field) 
   {
      if (!push(field))
         return CVector3(0,0,0);
      // Get vector
      CVector3 val(getVector3());
      // Pop stack
      pop();
      // Done
      return val;
   }

   CVector3 CLua::getVector3(unsigned int field)
   {
      if (!push(field))
         return CVector3(0,0,0);
      // Get vector
      CVector3 val(getVector3());
      // Pop stack
      pop();
      // Done
      return val;
   }

   CVector3 CLua::getVector3() 
   {
      // Get values
      float fX = getNumber("x");
      float fY = getNumber("y");
      float fZ = getNumber("z");
      // Done
      return CVector3(fX,fY,fZ);
   }


   CVector2 CLua::getVector2(const char* field) 
   {
      if (!push(field))
         return CVector2(0,0);
      // Get values
      float fX = getNumber("x");
      float fY = getNumber("y");
      // Pop stack
      pop();
      // Done
      return CVector2(fX,fY);
   }

}
