#ifndef SDS_LUA_H
#define SDS_LUA_H

#include "config.h"
#include "3D/Material.h"

extern "C" {
#include <lua.h>
}

namespace NSDIO {

   /**
    * Lua interpreter state.
    * Encapsulates a Lua interpreter state and it's stack.
    */
   class CLua {
      
   public:

      /**
       * Constructor.
       * @param filename The filename to interpret.
       */
      CLua(const char* filename);

      /**
       * Destructor.
       */
      ~CLua();

      /**
       * Open a global table.
       * @param table The name of the table to enter.
       * @return true if the table was pushed successfully.
       */
      bool setGlobalTable(const char* table);

      /**
       * Get float value for a field.
       * @param field The field name to access.
       * @return The value of the field. If the field wasn't found, the value is 0.
       */
      float getFloat(const char* field);

      /**
       * Get a string value for a field.
       * @param field The field name to access.
       * @return The contents of the field. It's the users responsibility to delete[] this pointer.
       */
      const char* getString(const char* field);

      /**
       * Get an RGBA colour value from a field.
       * @param field The field name to access.
       * @return The colour of the field.
       */
      CRGBAColour getColour(const char* field);

   private:

      /**
       * The Lua state object.
       */
      lua_State* m_pState;

   };

}

#endif // SDS_LUA_H
