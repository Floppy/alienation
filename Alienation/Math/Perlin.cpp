#include "Math/Perlin.h"

#include <iostream>
using namespace std;

#define PERLIN_SIZE 0x100

namespace NSDMath {

   const CVector3 CPerlin::m_avGradients[] = {
      CVector3( 1, 1, 0),
      CVector3(-1, 1, 0),
      CVector3( 1,-1, 0),
      CVector3(-1,-1, 0),
      CVector3( 1, 0, 1),
      CVector3(-1, 0, 1),
      CVector3( 1, 0,-1),
      CVector3(-1, 0,-1),
      CVector3( 0, 1, 1),
      CVector3( 0,-1, 1),
      CVector3( 0, 1,-1),
      CVector3( 0,-1,-1),
      CVector3( 1, 1, 0),
      CVector3(-1, 1, 0),
      CVector3( 0,-1, 1),
      CVector3( 0,-1,-1)
   };

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
         int j = permutation(randomInt());
         m_aiPermutation[i] = m_aiPermutation[j];
         m_aiPermutation[j] = temp;
      }   
   
      //for (int i=0; i<PERLIN_SIZE; i++) 
      //cout << (int)m_aiPermutation[i] << endl;

   }

   float CPerlin::noise(CVector3& vecPosition) {
   
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

      vX0 = wgradient(iX, iY, iZ, CVector3(fX0,fY0,fZ0));
      vX1 = wgradient(iX+1, iY, iZ, CVector3(fX1,fY0,fZ0));
      vY0 = lerp(fXS, vX0, vX1);

      vX0 = wgradient(iX, iY+1, iZ, CVector3(fX0,fY1,fZ0));
      vX1 = wgradient(iX+1, iY+1, iZ, CVector3(fX1,fY1,fZ0));
      vY1 = lerp(fXS, vX0, vX1);
      vZ0 = lerp(fYS, vY0, vY1);

      vX0 = wgradient(iX, iY, iZ+1, CVector3(fX0,fY0,fZ1));
      vX1 = wgradient(iX+1, iY, iZ+1, CVector3(fX1,fY0,fZ1));
      vY0 = lerp(fXS, vX0, vX1);

      vX0 = wgradient(iX, iY+1, iZ+1, CVector3(fX0,fY1,fZ1));
      vX1 = wgradient(iX+1, iY+1, iZ+1, CVector3(fX1,fY1,fZ1));
      vY1 = lerp(fXS, vX0, vX1);
      vZ1 = lerp(fYS, vY0, vY1);

      return lerp(fZS, vZ0, vZ1);
   }

   float CPerlin::noise(CVector2& vecPosition) {
   
      int iX = static_cast<int>(floor(vecPosition.X()));
      float fX0 = vecPosition.X() - iX;
      float fX1 = 1 - fX0;
      float fXS = spline(fX0);

      int iY = static_cast<int>(floor(vecPosition.Y()));
      float fY0 = vecPosition.Y() - iY;
      float fY1 = 1 - fY0;
      float fYS = spline(fY0);

      float vX0, vX1, vY0, vY1;

      vX0 = wgradient(iX, iY, 0, CVector3(fX0,fY0,0));
      vX1 = wgradient(iX+1, iY, 0, CVector3(fX1,fY0,0));
      vY0 = lerp(fXS, vX0, vX1);

      vX0 = wgradient(iX, iY+1, 0, CVector3(fX0,fY1,0));
      vX1 = wgradient(iX+1, iY+1, 0, CVector3(fX1,fY1,0));
      vY1 = lerp(fXS, vX0, vX1);

      return lerp(fYS, vY0, vY1);
   }

   float CPerlin::noise(float fPosition) {
   
      int iX = static_cast<int>(floor(fPosition));
      float fX0 = fPosition - iX;
      float fX1 = 1 - fX0;
      float fXS = spline(fX0);

      float vX0, vX1;

      vX0 = wgradient(iX, 0, 0, CVector3(fX0,0,0));
      vX1 = wgradient(iX+1, 0, 0, CVector3(fX1,0,0));
      return lerp(fXS, vX0, vX1);
   }

}
