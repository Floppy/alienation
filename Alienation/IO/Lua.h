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
       * @param index The index of the object to push.
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
       * Get numerical value for a table.
       * @param table The table name to access.
       * @return The value of the table. If the table wasn't found, the value is 0.
       */
      float getNumber(const char* table);

      /**
       * Get numerical value for a numbered table.
       * @param table The table number to access.
       * @return The value of the table. If the table wasn't found, the value is 0.
       */
      float getNumber(unsigned int table);

      /**
       * Get a string value for a table.
       * @param table The table name to access.
       * @return The contents of the table. It's the users responsibility to delete[] this pointer.
       */
      const char* getString(const char* table);

      /**
       * Get a string value for a numbered table.
       * @param table The table number to access.
       * @return The contents of the table. It's the users responsibility to delete[] this pointer.
       */
      const char* getString(unsigned int table);

      /**
       * Get an RGBA colour value from a table.
       * @param table The table name to access.
       * @return The colour of the table.
       */
      CRGBAColour getColour(const char* table);

      /**
       * Get an RGBA colour value from a numbered table.
       * @param table The table number to access.
       * @return The colour of the table.
       */
      CRGBAColour getColour(unsigned int table);

      /**
       * Get a 3D vector from a named table.
       * @param table The table name to access.
       * @return The vector from the table.
       */
      CVector3 getVector3(const char* table);

      /**
       * Get a 3D vector from a numbered table.
       * @param table The table number to access.
       * @return The vector from the table.
       */
      CVector3 getVector3(unsigned int table);

      /**
       * Get a 2D vector from a table.
       * @param table The table name to access.
       * @return The vector from the table.
       */
      CVector2 getVector2(const char* table);

      /**
       * Get a 2D vector from a numbered table.
       * @param table The table number to access.
       * @return The vector from the table.
       */
      CVector2 getVector2(unsigned int table);

   protected:

      /**
       * Get numerical value for the current table.
       * @return The value of the table. If the table wasn't found, the value is 0.
       */
      float getNumber();

      /**
       * Get a string value for the current table.
       * @return The contents of the table. It's the users responsibility to delete[] this pointer.
       */
      const char* getString();

      /**
       * Get an RGBA colour value from the current table.
       * @return The colour of the table.
       */
      CRGBAColour getColour();

      /**
       * Get a 3D vector from the current table
       * @return The vector from the table.
       */
      CVector3 getVector3();

      /**
       * Get a 2D vector from the current table
       * @return The vector from the table.
       */
      CVector2 getVector2();

   private:

      /**
       * The Lua state object.
       */
      lua_State* m_pState;

   };

}

#endif // SDS_LUA_H
