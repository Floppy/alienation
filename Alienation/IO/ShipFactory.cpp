#include "IO/ShipFactory.h"
#include "IO/Lua.h"
#include <string.h>

namespace NSDIO {

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

      // Return a new ship
      return NULL;
   }
   
}
