#include "IO/WeaponFactory.h"

namespace NSDIO {

   CWeapon* CWeaponFactory::load(const char *strFileName) {
      return new CWeapon(CVector3(0.0f, -0.3f, -3.3f),
                         1.0f,7.0f,235.0f,0.5f,
                         "weapon.wav","ball.png",
                         CRGBAColour(1.0f,0.2f,0.4f,1.0f));
   }
   
}
