#include "Math/Chaos.h"

namespace NSDMath {

   CChaos::CChaos(unsigned long ulSeed, float fH, float fLacunarity, float fOctaves) :
      m_oPerlin(ulSeed),
      m_fH(fH),
      m_fLacunarity(fLacunarity),
      m_fOctaves(fOctaves),
      m_pfExponents(NULL)
   {
      generateExponents();
   }

   CChaos::~CChaos() {
      delete [] m_pfExponents;
   }

   void CChaos::init(unsigned long ulSeed)
   {
      // Re-seed noise generator
      m_oPerlin.init(ulSeed);
   }

   void CChaos::changeParams(float fH, float fLacunarity, float fOctaves) 
   {
      // Store values
      m_fH = fH;
      m_fLacunarity = fLacunarity;
      m_fOctaves = fOctaves;
      // Generate exponent array
      generateExponents();
   }

   void CChaos::generateExponents()
   {
      // Dump old exponent array
      delete [] m_pfExponents;
      
      // Allocate exponent array
      m_pfExponents = new float[static_cast<int>(m_fOctaves+1)];

      // Compute weights
      for (int i=0; i<=m_fOctaves+1; i++)
         m_pfExponents[i] = pow(m_fLacunarity, -i*m_fH);

   }

   float CChaos::fBmMono(CVector3 vecPosition) 
   {
      float val(0.0);
      int i;
      // Sum
      for (i=0; i<m_fOctaves; i++) {
         val += m_oPerlin.noise(vecPosition) * m_pfExponents[i];
         vecPosition *= m_fLacunarity;
      }
      // Deal with partial octaves      
      float fRemain = m_fOctaves - static_cast<int>(m_fOctaves);
      if (fRemain != 0) {
         val += fRemain * m_oPerlin.noise(vecPosition) * m_pfExponents[i];
      }
      // Done
      return val;
   }

   float CChaos::fBmMulti(CVector3 vecPosition, float fOffset) 
   {
      float val(1.0);
      int i;
      // Convolve
      for (i=0; i<m_fOctaves; i++) {
         val *= m_pfExponents[i] * m_oPerlin.noise(vecPosition) + 1.0;
         vecPosition *= m_fLacunarity;
      }
      // Deal with partial octaves      
      float fRemain = m_fOctaves - static_cast<int>(m_fOctaves);
      if (fRemain != 0) {
         val += fRemain * m_pfExponents[i] * m_oPerlin.noise(vecPosition) + 1.0 ;
      }
      // Done
      return val;
   }

   float CChaos::fBmPow(CVector3 vecPosition) {
      // Evaluate fBm
      float val(fBmMono(vecPosition));
      // Apply power function
      if (val <= 0.0f)
         return (float)-pow(-val, 0.7f);
      return (float)pow(val, 1 + m_oPerlin.noise(vecPosition) * val);
   }


   float CChaos::turbulence(CVector3 vecPosition) 
   {
      float val(0.0);
      int i;
      // Sum
      for (i=0; i<m_fOctaves; i++) {
         val += fabs(m_oPerlin.noise(vecPosition) * m_pfExponents[i]);
         vecPosition *= m_fLacunarity;
      }
      // Deal with partial octaves      
      float fRemain = m_fOctaves - static_cast<int>(m_fOctaves);
      if (fRemain != 0) {
         val += fabs(fRemain * m_oPerlin.noise(vecPosition) * m_pfExponents[i]);
      }
      // Done
      return val;
   }

}
