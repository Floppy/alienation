#ifndef SDS_ASTEROID_H
#define SDS_ASTEROID_H

#include "config.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Game/GameObject.h"

enum TAsteroidType {
   ROID_COMMON,
   ROID_GOLD,
   ROID_ICE,
   ROID_RED
};

class CAsteroid : public CGameObject
{

 public:
   
   CAsteroid(int num, float mass);
   
   virtual ~CAsteroid();
   
   void load(TAsteroidType type);

};

#endif // SDS_ASTEROID_H
