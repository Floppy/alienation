#ifndef SDS_LUA_H
#define SDS_LUA_H

#include "config.h"
#include "3D/Material.h"
#include "Math/Vector.h"

extern "C" {
#include <lua.h>
}

namespace NSDIO {

   using namespace NSDMath;

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
       * Push a name onto the stack.
       * @param name The name of the object to push.
       * @param type The type of the object expected. These types are defined in lua.h.
       * @return true if the table was pushed successfully and was the correct type.
       */
      bool push(const char* name, int type = LUA_TTABLE);

      /**
       * Push an indexed value onto the stack.
       * @param name The index of the object to push.
       * @param type The type of the object expected. These types are defined in lua.h.
       * @return true if the table was pushed successfully and was the correct type.
       */
      bool push(unsigned int index, int type = LUA_TTABLE);

      /**
       * Get size of current table.
       * @return The size of the table.
       */
      unsigned int tableSize();

      /**
       * Exit the current sub-table.
       */
      void pop();

      /**
       * Get numerical value for a field.
       * @param field The field name to access.
       * @return The value of the field. If the field wasn't found, the value is 0.
       */
      float getNumber(const char* field);

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

      /**
       * Get a 3D vector from a named field.
       * @param field The field name to access.
       * @return The vector from the field.
       */
      CVector3 getVector3(const char* field);

      /**
       * Get a 3D vector from a numbered field.
       * @param field The field number to access.
       * @return The vector from the field.
       */
      CVector3 getVector3(unsigned int field);

      CVector3 getVector3();

      /**
       * Get a 2D vector from a field.
       * @param field The field name to access.
       * @return The vector from the field.
       */
      CVector2 getVector2(const char* field);

   private:

      /**
       * The Lua state object.
       */
      lua_State* m_pState;

   };

}

#endif // SDS_LUA_H
