#ifndef ALIENATION_PERLIN_H
#define ALIENATION_PERLIN_H

#include "config.h"
#include "Math/Random.h"
#include "Math/Vector.h"

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
   float noise(CVector3& vecPosition);

   /**
    * Calculate 2D noise.
    * @param vecPosition 2D position of noise sample.
    */
   float noise(CVector2& vecPosition);

   /**
    * Calculate 1D noise.
    * @param dPosition 1D position of noise sample.
    */
   float noise(float fPosition);

 protected:

   /**
    * Generate the m_aiPermutation array.
    * Generates a random permutation of the numbers 0..255 in the m_aiPermutation array.
    */
   void permuteP(void);

   /**
    * Permutation function.
    * Generate an index into m_aiPermutation for any integer.
    */
   int permutation(int iX)
   { return iX & 0xFF; }

   /**
    * Get the gradient for a 3d lattice point.
    */
   const CVector3* gradient(int iX, int iY, int iZ)
   { return m_avGradients + (permutation(iX + permutation(iY + permutation(iZ))) & 0xF); }

   /**
    * Get the sum of the weighted gradient for a 3d lattice point.
    */
   float wgradient(int iX, int iY, int iZ, CVector3 weight)
   { 
      const CVector3* pGradient = gradient(iX,iY,iZ);
      return pGradient->X()*weight.X() + pGradient->Y()*weight.Y() + pGradient->Z()*weight.Z(); 
   }

   /**
    * Spline function.
    * s(t) = 6t^5 - 15t^4 + 10t^3
    */
   float spline(float fT)
   { return fT*fT*fT * ( (6*fT*fT) - (15*fT) + 10 ); }

   /**
    * Linear interpolation function.
    * l(a,m,n) = a*m + (1-a)*n
    */
   float lerp(float fA, float fM, float fN)
   { return fM + (fA * (fN - fM)); }

   /**
    * Random number generator.
    */
   CRandom m_oRandom;

   /**
    * Permutation array.
    */
   unsigned char m_aiPermutation[0x100];
   
   /**
    * Gradient array.
    */
   static CVector3 m_avGradients[0x10];

};

#endif //ALIENATION_PERLIN_H

