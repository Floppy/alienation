#ifndef ALIENATION_RANDOM_H
#define ALIENATION_RANDOM_H

#include "config.h"

namespace NSDMath {

   /**
    * The maximum value of a random unsigned int.
    */
   const unsigned long KMaxRandomUInt = 0xffffffff;

   /**
    * The maximum value of a random int.
    */
   const long KMaxRandomInt = 0x7fffffff;

   /**
    * Get a random unsigned integer.
    * @return An unsigned long integer between 0 and KMaxRandomUInt inclusive.
    */
   unsigned long randomUInt();

   /**
    * Get a random integer.
    * @return A long integer between 0 and KMaxRandomInt inclusive.
    */
   long randomInt();
  
   /**
    * Get a random floating point number.
    * @return A double-precision floating point number between 0 and 1.
    */
   double random01();

   /**
    * Set seed for the random01 and randomUInt functions.
    * @param seed An integer value to seed the generator with.
    */
   void randomSeed(unsigned long seed);

   /**
    * A random number generator.
    * This is based on the Mersenne Twister algorithm, in particular the 
    * implementation by Shawn Cokus.
    *
    * <pre>
    * Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura,
    * All rights reserved.                          
    *
    * Redistribution and use in source and binary forms, with or without
    * modification, are permitted provided that the following conditions
    * are met:
    *
    *   1. Redistributions of source code must retain the above copyright
    *      notice, this list of conditions and the following disclaimer.
    *
    *   2. Redistributions in binary form must reproduce the above copyright
    *      notice, this list of conditions and the following disclaimer in the
    *      documentation and/or other materials provided with the distribution.
    *
    *   3. The names of its contributors may not be used to endorse or promote 
    *      products derived from this software without specific prior written 
    *      permission.
    *
    * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    * A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
    * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
    * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
    * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
    * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
    * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
    * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
    * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
    * </pre>
    */
   class CRandom {

   public:

      /**
       * Constructor.
       */
      CRandom();

      /**
       * Constructor with seed.
       * @param ulSeed Random seed to use for initialisation.
       */
      CRandom(unsigned long ulSeed);

      /**
       * Initialise random number generator.
       * @param ulSeed Random seed to use for initialisation.
       */
      void seed(unsigned long ulSeed);

      /**
       * Initialise random number generator with very long seed.
       * @param pulSeed Array containing seed value.
       * @param ulSeedLength Length of pulSeed array.
       */
      void seed(unsigned long *pulSeed, unsigned long ulSeedLength);

      /**
       * Generate random unsigned integer.
       * @return An unsigned long integer between 0 and KMaxRandomUInt inclusive.
       */
      unsigned long randUInt(void);

      /**
       * Generate a random integer.
       * @return A long integer between 0 and KMaxRandomInt inclusive.
       */
      long randInt(void);

      /**
       * Get a random floating point number.
       * @return A double-precision floating point number between 0 and 1.
       */
      double randDouble(void);

      /**
       * Get a random floating point number.
       * This has a slightly different range to randDouble.
       * @return A double-precision floating point number between 0 and 1.
       */
      double randDouble2(void);

      /**
       * Get a random floating point number.
       * This has a slightly different range to randDouble and randDouble2.
       * @return A double-precision floating point number between 0 and 1.
       */
      double randDouble3(void);

      /**
       * Get a random 53 bit floating point number.
       * @return A double-precision floating point number between 0 and 1.
       */
      double randDouble53(void);

   protected:

      /**
       * Move to next state.
       */
      void nextState(void);

      /**
       * How many states left?
       */
      int m_iLeft;

      /**
       * Is initialisation complete?
       */
      int m_bInit;

      /**
       * Pointer to next state.
       */
      unsigned long *m_pNext;   

      /**
       * The array for the state vector
       */
      unsigned long m_aulState[624];

   };

}

#endif //ALIENATION_RANDOM_H

   
