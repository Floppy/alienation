#include "Game/Asteroid.h"
#include "IO/3ds.h"
#include "Math/Random.h"

static const char* roidfiles[] = {
   "Data/Model/roid1.3ds",
   "Data/Model/gold1.3ds",
   "Data/Model/gold2.3ds",
   "Data/Model/ice1.3ds",
   "Data/Model/redcrystal1.3ds",
   "Data/Model/redcrystal2.3ds",
   "Data/Model/redcrystal3.3ds",
};


CAsteroid::CAsteroid(int num, float mass) : CGameObject(num, mass)
{
}

CAsteroid::~CAsteroid()
{
}

//load model, trail texture and brake texture
void CAsteroid::load(TAsteroidType type)
{

   static CRandom prng(37473);

   // Select model
   const char* strRoidFile = NULL;
   float fRandom(prng.randDouble());

   switch (type) {
   case ROID_GOLD:
      strRoidFile = fRandom > 0.5 ? roidfiles[1] : roidfiles[2];
      break;
   case ROID_ICE:
      strRoidFile = roidfiles[3];
      break;
   case ROID_RED:      
      if (fRandom < 0.333)
         strRoidFile = roidfiles[4];
      if (fRandom < 0.667)
         strRoidFile = roidfiles[5];
      else
         strRoidFile = roidfiles[6];
      break;
   case ROID_COMMON:
   default:
      strRoidFile = roidfiles[0];
      break;
   }

   // Load model
   NSDIO::CLoad3DS oLoad3ds;
   if (oLoad3ds.import3DS(&(m_oModel), strRoidFile)) {
      m_oModel.init();
   }  

   // Set position
   CVector3 pos((prng.randDouble()-0.5) * 5000,(prng.randDouble()-0.5) * 5000,(prng.randDouble()-0.5) * 5000);
   m_ppMasses[0]->m_vecPos = pos;   

}

