#ifndef SDS_BOUNDINGSPHERE_H
#define SDS_BOUNDINGSPHERE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Math/Vector.h"

using namespace NSDMath;

class CBoundingSphere  
{

public:

   /*
    * Constructor.
    */
   CBoundingSphere();
   
   /**
    * Sphere centre.
    */
   CVector3 m_vecPos; 
   
   /**
    * Sphere radius.
    */
   float m_fRadius;
   
};

#endif // SDS_BOUNDINGSPHERE_H
