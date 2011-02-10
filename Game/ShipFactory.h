#ifndef SDS_SHIPFACTORY_H
#define SDS_SHIPFACTORY_H

#include "config.h"
#include "Game/Ship.h"

//namespace NSDIO {

   /**
    * Load a CShip from a Lua script.
    */
   class CShipFactory {
      
   public:
      
      /** 
       * Load a CShip from a Lua script.
       * @param strFileName The filename to load.
       * @param bPlayer Create a ship for the local player?
       * @return A pointer to the loaded ship. NULL if the ship could not be loaded.
       */
      static CShip* load(const char *strFileName, bool bPlayer=false);
      
   };
      
//}

#endif // SDS_SHIPFACTORY_H
