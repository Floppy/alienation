#ifndef ALIENATION_PERLIN_H
#define ALIENATION_PERLIN_H

#include "config.h"
#include "Math/Random.h"
#include "Math/Vector.h"

namespace NSDMath {

   /**
    * A Perlin Noise generator.
    * This uses the "improved" noise function proposed by Perlin.
    * Should be more efficient and give better results than the standard one.
    */
   class CPerlin {

   public:

      /**
       * Constructor.
       * Calls init() internally.
       * @param ulSeed Seed value for random number generator.
       */
      CPerlin(unsigned long ulSeed);

      /**
       * Initialise noise generator.
       * @param ulSeed Seed value for random number generator.
       */
      void init(unsigned long ulSeed);

      /**
       * Calculate 3D noise.
       * @param vecPosition 3D position of noise sample.
       */
      float noise(const CVector3& vecPosition);

      /**
       * Calculate 2D noise.
       * @param vecPosition 2D position of noise sample.
       */
      float noise(const CVector2& vecPosition);

      /**
       * Calculate 1D noise.
       * @param fPosition 1D position of noise sample.
       */
      float noise(float fPosition);

   protected:

      /**
       * Generate the m_aiPermutation array.
       * Generates a random permutation of the numbers 0..255 in the m_aiPermutation array.
       */
      void permuteP(void);

      /**
       * Calculate the lattice gradient for a 3d point inside the cell.
       */
      float gradient(int hash, float fX, float fY, float fZ)
      { 
         int h = hash & 0xF;
         double u = h<8||h==12||h==13 ? fX : fY;
         double v = h<4||h==12||h==13 ? fY : fZ;
         return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
      }

      /**
       * Spline function.
       * s(t) = 6t^5 - 15t^4 + 10t^3
       */
      float spline(float fT)
      { return fT * fT * fT * ( fT * (fT * 6 - 15) + 10 ); }

      /**
       * Linear interpolation function.
       * l(t,a,b) = (1-t)*a + t*b
       */
      float lerp(float fT, float fA, float fB)
      { return fA + fT * (fB - fA); }

      /**
       * Random number generator.
       */
      CRandom m_oRandom;

      /**
       * Permutation array.
       */
      unsigned char m_aiPermutation[0x200];
   
   };

}

#endif //ALIENATION_PERLIN_H
