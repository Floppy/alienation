#ifndef SDS_WEAPONFACTORY_H
#define SDS_WEAPONFACTORY_H

#include "config.h"
#include "Math/Vector.h"
#include "3D/Material.h"
#include "Game/Weapon.h"

namespace NSDIO {

   /**
    * Load a CWeapon from a Lua script.
    */
   class CWeaponFactory {
      
   public:
      
      /** 
       * Load a CWeapon from a Lua script.
       * @param strFileName The filename to load.
       * @return A pointer to the loaded weapon. NULL if the weapon could not be loaded.
       */
      static CWeapon* load(const char *strFileName);
      
   };
      
}

#endif // SDS_WEAPONFACTORY_H
