#include "Math/Perlin.h"

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

   float CPerlin::noise(const CVector3& vecPosition) {
   
      int X = static_cast<int>(floor(vecPosition.X())) & 255;
      int Y = static_cast<int>(floor(vecPosition.Y())) & 255;
      int Z = static_cast<int>(floor(vecPosition.Z())) & 255;
      
      double x = vecPosition.X() - floor(vecPosition.X());
      double y = vecPosition.Y() - floor(vecPosition.Y());
      double z = vecPosition.Z() - floor(vecPosition.Z());

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
   }

   float CPerlin::noise(const CVector2& vecPosition) {
      return noise(CVector3(vecPosition.X(),vecPosition.Y(),0.5));
   }

   float CPerlin::noise(float fPosition) {
      return noise(CVector3(fPosition,0.5,0.5));
   }

}
