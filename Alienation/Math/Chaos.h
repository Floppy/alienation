#ifndef ALIENATION_CHAOS_H
#define ALIENATION_CHAOS_H

#include "config.h"
#include "Math/Perlin.h"
#include "Math/Vector.h"

namespace NSDMath {

   /**
    * A chaotic function generator.
    * This contains fBm function and versions thereof,
    * which are generalisations of Perlin's "chaos" function.
    */
   class CChaos {

   public:

      /**
       * Constructor.
       * @param ulSeed Seed value for noise generator.
       * @param fH Fractal increment.
       * @param fLacunarity Gap between successive frequencies.
       * @param fOctaves How many frequencies in the fBm - maximum of 10.
       */
      CChaos(unsigned long ulSeed, float fH, float fLacunarity, float fOctaves);

      /**
       * Destructor.
       */
      ~CChaos();

      /**
       * Reinitialise chaos generator.
       * Changes underlying noise function.
       * @param ulSeed Seed value for noise generator.
       */
      void init(unsigned long ulSeed);

      /**
       * Change parameters.
       * Changes parameters on the fly without modifying the underlying noise.
       * Can be used to modify number of octaves during computation.
       * @param fH Fractal increment.
       * @param fLacunarity Gap between successive frequencies.
       * @param fOctaves How many frequencies in the fBm - maximum of 10.
       */
      void changeParams(float fH, float fLacunarity, float fOctaves);

      /** 
       * Calculate basic monofractal fBm function.
       * @param vecPosition 3d position of sample.
       */
      float fBmMono(CVector3 vecPosition);

      /** 
       * Calculate multifractal fBm function.
       * @param vecPosition 3d position of sample.
       * @param fOffset Determines the multifractality.
       */
      float fBmMulti(CVector3 vecPosition, float fOffset);

      /** 
       * Calculate power multifractal fBm function.
       * This applies the power function to the result of basic fBm. 
       * It should give a smoother surface at lower values.
       * @param vecPosition 3d position of sample.
       */
      float fBmPow(CVector3 vecPosition);

      /** 
       * Calculate turbulence function.
       * This is just fBm done with the absolute value of the perlin noise.
       * @param vecPosition 3d position of sample.
       */
      float turbulence(CVector3 vecPosition);

   protected:

      /**
       * Generate exponent array.
       * Old exponent array is destroyed.
       */
      void generateExponents();

      /**
       * Perlin noise generator.
       */
      CPerlin m_oPerlin;

      /**
       * Fractal increment
       */
      float m_fH;

      /**
       * Lacunarity
       */
      float m_fLacunarity;

      /**
       * Number of octaves to use.
       */
      float m_fOctaves;

      /**
       * Exponent array for fBm
       */
      float* m_pfExponents;

   };

}

#endif //ALIENATION_CHAOS_H
