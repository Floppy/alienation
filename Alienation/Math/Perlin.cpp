#include "Math/Perlin.h"

#include <iostream>
using namespace std;

#define PERLIN_SIZE 0x100

namespace NSDMath {

   CPerlin::CPerlin(unsigned long ulSeed) 
   {
      // Initialise
      init(ulSeed);
   }

   void CPerlin::init(unsigned long ulSeed) 
   {
      // Re-seed random number generator
      m_oRandom.seed(ulSeed);
      // Generate permutation array
      permuteP();
      // Done
      return;
   }

   void CPerlin::permuteP(void) 
   {
      int i;
      // Fill array
      for (i=0; i<PERLIN_SIZE; i++) 
      {
         m_aiPermutation[i] = i;
      }
      // Permute
      unsigned char temp;
      for (i=0; i<PERLIN_SIZE; i++) 
      {
         temp = m_aiPermutation[i];
         int j = m_oRandom.randInt() & 0xFF;
         m_aiPermutation[i] = m_aiPermutation[j];
         m_aiPermutation[j] = temp;
      }   
      // Extend
      for (i=0; i<PERLIN_SIZE ; i++) 
         m_aiPermutation[i+256] = m_aiPermutation[i]; 
   }

   float CPerlin::noise(CVector3& vecPosition) {
   
      int X = static_cast<int>(floor(vecPosition.X())) & 255;
      int Y = static_cast<int>(floor(vecPosition.Y())) & 255;
      int Z = static_cast<int>(floor(vecPosition.Z())) & 255;
      
      double x = floor(vecPosition.X());
      double y = floor(vecPosition.Y());
      double z = floor(vecPosition.Z());

      double u = spline(x);
      double v = spline(y);
      double w = spline(z);

      int A  = m_aiPermutation[X  ]+Y;
      int AA = m_aiPermutation[A  ]+Z;
      int AB = m_aiPermutation[A+1]+Z;
      int B  = m_aiPermutation[X+1]+Y;
      int BA = m_aiPermutation[B  ]+Z;
      int BB = m_aiPermutation[B+1]+Z;

      return lerp(w, lerp(v, lerp(u, gradient(m_aiPermutation[AA  ], x  , y  , z   ),
                                     gradient(m_aiPermutation[BA  ], x-1, y  , z   )),
                             lerp(u, gradient(m_aiPermutation[AB  ], x  , y-1, z   ),
                                     gradient(m_aiPermutation[BB  ], x-1, y-1, z   ))),
                     lerp(v, lerp(u, gradient(m_aiPermutation[AA+1], x  , y  , z-1 ),
                                     gradient(m_aiPermutation[BA+1], x-1, y  , z-1 )),
                             lerp(u, gradient(m_aiPermutation[AB+1], x  , y-1, z-1 ),
                                     gradient(m_aiPermutation[BB+1], x-1, y-1, z-1 ))));


      /*
      int iX = static_cast<int>(floor(vecPosition.X()));
      float fX0 = vecPosition.X() - iX;
      float fX1 = 1 - fX0;
      float fXS = spline(fX0);

      int iY = static_cast<int>(floor(vecPosition.Y()));
      float fY0 = vecPosition.Y() - iY;
      float fY1 = 1 - fY0;
      float fYS = spline(fY0);

      int iZ = static_cast<int>(floor(vecPosition.Z()));
      float fZ0 = vecPosition.Z() - iZ;
      float fZ1 = 1 - fZ0;
      float fZS = spline(fZ0);

      float vX0, vX1, vY0, vY1, vZ0, vZ1;

      vX0 = gradient(iX, iY, iZ, fX0, fY0, fZ0);
      vX1 = gradient(iX+1, iY, iZ, fX1, fY0, fZ0);
      vY0 = lerp(fXS, vX0, vX1);

      vX0 = gradient(iX, iY+1, iZ, fX0, fY1, fZ0);
      vX1 = gradient(iX+1, iY+1, iZ, fX1, fY1, fZ0);
      vY1 = lerp(fXS, vX0, vX1);
      vZ0 = lerp(fYS, vY0, vY1);

      vX0 = gradient(iX, iY, iZ+1, fX0, fY0, fZ1);
      vX1 = gradient(iX+1, iY, iZ+1, fX1, fY0, fZ1);
      vY0 = lerp(fXS, vX0, vX1);

      vX0 = gradient(iX, iY+1, iZ+1, fX0, fY1, fZ1);
      vX1 = gradient(iX+1, iY+1, iZ+1, fX1, fY1, fZ1);
      vY1 = lerp(fXS, vX0, vX1);
      vZ1 = lerp(fYS, vY0, vY1);

      return lerp(fZS, vZ0, vZ1);
      */
   }

   float CPerlin::noise(CVector2& vecPosition) {
   
      /*
      int iX = static_cast<int>(floor(vecPosition.X()));
      float fX0 = vecPosition.X() - iX;
      float fX1 = 1 - fX0;
      float fXS = spline(fX0);

      int iY = static_cast<int>(floor(vecPosition.Y()));
      float fY0 = vecPosition.Y() - iY;
      float fY1 = 1 - fY0;
      float fYS = spline(fY0);

      float vX0, vX1, vY0, vY1;

      vX0 = gradient(iX, iY, 0, fX0, fY0, 0);
      vX1 = gradient(iX+1, iY, 0, fX1, fY0, 0);
      vY0 = lerp(fXS, vX0, vX1);

      vX0 = gradient(iX, iY+1, 0, fX0, fY1, 0);
      vX1 = gradient(iX+1, iY+1, 0, fX1, fY1, 0);
      vY1 = lerp(fXS, vX0, vX1);

      return lerp(fYS, vY0, vY1);
      */
      return 0;
   }

   float CPerlin::noise(float fPosition) {
   
      /*
      int iX = static_cast<int>(floor(fPosition));
      float fX0 = fPosition - iX;
      float fX1 = 1 - fX0;
      float fXS = spline(fX0);

      float vX0, vX1;

      vX0 = gradient(iX, 0, 0, fX0, 0, 0);
      vX1 = gradient(iX+1, 0, 0, fX1, 0, 0);
      return lerp(fXS, vX0, vX1);
      */
      return 0;
   }

}
