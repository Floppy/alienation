#include "Math/Random.h"

CRandom g_oTwister;

unsigned long randomUInt() {
   return g_oTwister.randUInt();
}

long randomInt() {
   return g_oTwister.randInt();
}
  
double random01() {
   return g_oTwister.randDouble();
}

void randomSeed(unsigned long seed) {
   g_oTwister.seed(seed);
}

/**
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
 */

/* Mersenne Twister Parameters */  
#define N 624
#define M 397
#define MATRIX_A 0x9908b0dfUL   /* constant vector a */
#define UMASK 0x80000000UL /* most significant w-r bits */
#define LMASK 0x7fffffffUL /* least significant r bits */
#define MIXBITS(u,v) ( ((u) & UMASK) | ((v) & LMASK) )
#define TWIST(u,v) ((MIXBITS(u,v) >> 1) ^ ((v)&1UL ? MATRIX_A : 0UL))

CRandom::CRandom() :
   m_iLeft(1),
   m_bInit(false),
   m_pNext(NULL)
{
}

void CRandom::seed(unsigned long s)
{
   int j;
   m_aulState[0]= s & 0xffffffffUL;
   for (j=1; j<N; j++) {
      m_aulState[j] = (1812433253UL * (m_aulState[j-1] ^ (m_aulState[j-1] >> 30)) + j); 
      /* See Knuth TAOCP Vol2. 3rd Ed. P.106 for multiplier. */
      /* In the previous versions, MSBs of the seed affect   */
      /* only MSBs of the array m_aulState[].                        */
      /* 2002/01/09 modified by Makoto Matsumoto             */
      m_aulState[j] &= 0xffffffffUL;  /* for >32 bit machines */
   }
   m_iLeft = 1; 
   m_bInit = true;
}

void CRandom::seed(unsigned long *init_key, unsigned long key_length)
{
   int i, j, k;
   seed(19650218UL);
   i=1; j=0;
   k = (N>key_length ? N : key_length);
   for (; k; k--) {
      m_aulState[i] = (m_aulState[i] ^ ((m_aulState[i-1] ^ (m_aulState[i-1] >> 30)) * 1664525UL))
          + init_key[j] + j; /* non linear */
      m_aulState[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
      i++; j++;
      if (i>=N) { m_aulState[0] = m_aulState[N-1]; i=1; }
      if (j>=key_length) j=0;
   }
   for (k=N-1; k; k--) {
      m_aulState[i] = (m_aulState[i] ^ ((m_aulState[i-1] ^ (m_aulState[i-1] >> 30)) * 1566083941UL))
         - i; /* non linear */
      m_aulState[i] &= 0xffffffffUL; /* for WORDSIZE > 32 machines */
      i++;
      if (i>=N) { m_aulState[0] = m_aulState[N-1]; i=1; }
   }
   
   m_aulState[0] = 0x80000000UL; /* MSB is 1; assuring non-zero initial array */ 
   m_iLeft = 1; 
   m_bInit = true;
}

void CRandom::nextState(void)
{
   unsigned long *p=m_aulState;
   int j;
   
   /* if seed() has not been called, */
   /* a default initial seed is used         */
   if (!m_bInit) seed(5489UL);
   
   m_iLeft = N;
   m_pNext = m_aulState;
   
   for (j=N-M+1; --j; p++) 
      *p = p[M] ^ TWIST(p[0], p[1]);
   
   for (j=M; --j; p++) 
      *p = p[M-N] ^ TWIST(p[0], p[1]);
   
   *p = p[M-N] ^ TWIST(p[0], m_aulState[0]);
}

unsigned long CRandom::randUInt(void)
{
   unsigned long y;
   
   if (--m_iLeft == 0) nextState();
   y = *m_pNext++;
   
   /* Tempering */
   y ^= (y >> 11);
   y ^= (y << 7) & 0x9d2c5680UL;
   y ^= (y << 15) & 0xefc60000UL;
   y ^= (y >> 18);
   
   return y;
}

long CRandom::randInt(void)
{
    unsigned long y;

    if (--m_iLeft == 0) nextState();
    y = *m_pNext++;

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return (long)(y>>1);
}

double CRandom::randDouble(void)
{
    unsigned long y;

    if (--m_iLeft == 0) nextState();
    y = *m_pNext++;

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return (double)y * (1.0/4294967295.0); 
    /* divided by 2^32-1 */ 
}

double CRandom::randDouble2(void)
{
    unsigned long y;

    if (--m_iLeft == 0) nextState();
    y = *m_pNext++;

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return (double)y * (1.0/4294967296.0); 
    /* divided by 2^32 */
}

double CRandom::randDouble3(void)
{
    unsigned long y;

    if (--m_iLeft == 0) nextState();
    y = *m_pNext++;

    /* Tempering */
    y ^= (y >> 11);
    y ^= (y << 7) & 0x9d2c5680UL;
    y ^= (y << 15) & 0xefc60000UL;
    y ^= (y >> 18);

    return ((double)y + 0.5) * (1.0/4294967296.0); 
    /* divided by 2^32 */
}

double CRandom::randDouble53(void) 
{ 
    unsigned long a=randUInt()>>5, b=randUInt()>>6; 
    return(a*67108864.0+b)*(1.0/9007199254740992.0); 
} 

