#ifndef ALIENATION_PERLIN_H
#define ALIENATION_PERLIN_H

#include "config.h"
#include "Math/Random.h"

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

 protected:

   /**
    * Permute the m_aiP array.
    * Generates a random permutation of the numbers 0..255 in the m_aiP array.
    */
   void PermuteP(void);

   /**
    * Random number generator.
    */
   CRandom m_oRandom;

};

#endif //ALIENATION_PERLIN_H

