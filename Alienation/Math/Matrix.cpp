#include "Math/Matrix.h"

CMatrix::CMatrix()
{
   loadIdentity();
}

CMatrix::CMatrix(const CVector3& axis, float theta)
{
   CQuat oQuat(axis, theta);
   *this = CMatrix(oQuat);
}

CMatrix::CMatrix(const CQuat& quat)
{
   float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
   // Calculate coefficients
   x2 = quat.X() + quat.X();
   y2 = quat.Y() + quat.Y();
   z2 = quat.Z() + quat.Z();
   xx = quat.X() * x2;
   xy = quat.X() * y2;
   xz = quat.X() * z2;
   yy = quat.Y() * y2;
   yz = quat.Y() * z2;
   zz = quat.Z() * z2;
   wx = quat.W() * x2;
   wy = quat.W() * y2;
   wz = quat.W() * z2;
   // Calculate elements
   m_afElement[0] = 1.0f - (yy + zz);
   m_afElement[1] = xy - wz;
   m_afElement[2] = xz + wy;
   m_afElement[3] = 0.0;
   m_afElement[4] = xy + wz;
   m_afElement[5] = 1.0f - (xx + zz);
   m_afElement[6] = yz - wx;
   m_afElement[7] = 0.0;
   m_afElement[8] = xz - wy;
   m_afElement[9] = yz + wx;
   m_afElement[10] = 1.0f - (xx + yy);
   m_afElement[11] = 0.0;
   m_afElement[12] = 0;
   m_afElement[13] = 0;
   m_afElement[14] = 0;
   m_afElement[15] = 1;
}

CMatrix::CMatrix(GLenum glMatrix) {
   glGetFloatv(glMatrix,m_afElement);   
}

CMatrix::CMatrix(const CMatrix& oMatrix) 
{
   for (int i=0; i<16; i++) 
      m_afElement[i] = oMatrix.m_afElement[i];
}

void CMatrix::loadIdentity()
{
   // Row 0
   m_afElement[0]=1.0f;
   m_afElement[1]=0.0f;
   m_afElement[2]=0.0f;
   m_afElement[3]=0.0f;
   // Row 1   
   m_afElement[4]=0.0f;
   m_afElement[5]=1.0f;
   m_afElement[6]=0.0f;
   m_afElement[7]=0.0f;
   // Row 2   
   m_afElement[8]=0.0f;
   m_afElement[9]=0.0f;
   m_afElement[10]=1.0f;
   m_afElement[11]=0.0f;
   // Row 3   
   m_afElement[12]=0.0f;
   m_afElement[13]=0.0f;
   m_afElement[14]=0.0f;
   m_afElement[15]=1.0f;
}

CMatrix& CMatrix::operator=(const CMatrix& oMatrix) 
{
   for (int i=0; i<16; i++) 
      m_afElement[i] = oMatrix.m_afElement[i];
   return *this;
}



CMatrix& CMatrix::operator*=(const CMatrix& oMatrix)
{
   CMatrix temp(*this);
   
   m_afElement[0] = temp.m_afElement[0 ]*oMatrix.m_afElement[0 ] 
      + temp.m_afElement[4 ]*oMatrix.m_afElement[1 ]
      + temp.m_afElement[8 ]*oMatrix.m_afElement[2 ]
      + temp.m_afElement[12]*oMatrix.m_afElement[3 ];
   
   m_afElement[1] = temp.m_afElement[1 ]*oMatrix.m_afElement[0 ]
      + temp.m_afElement[5 ]*oMatrix.m_afElement[1 ]
      + temp.m_afElement[9 ]*oMatrix.m_afElement[2 ]
      + temp.m_afElement[13]*oMatrix.m_afElement[3 ];
   
   m_afElement[2] = temp.m_afElement[2 ]*oMatrix.m_afElement[0 ]
      + temp.m_afElement[6 ]*oMatrix.m_afElement[1 ]
      + temp.m_afElement[10]*oMatrix.m_afElement[2 ]
      + temp.m_afElement[14]*oMatrix.m_afElement[3 ];
   
   m_afElement[3] = temp.m_afElement[3 ]*oMatrix.m_afElement[0 ]
      + temp.m_afElement[7 ]*oMatrix.m_afElement[1 ]
      + temp.m_afElement[11]*oMatrix.m_afElement[2 ]
      + temp.m_afElement[15]*oMatrix.m_afElement[3 ];
   
   m_afElement[4] = temp.m_afElement[0 ]*oMatrix.m_afElement[4 ]
      + temp.m_afElement[4 ]*oMatrix.m_afElement[5 ]
      + temp.m_afElement[8 ]*oMatrix.m_afElement[6 ]
      + temp.m_afElement[12]*oMatrix.m_afElement[7 ];
   
   m_afElement[5] = temp.m_afElement[1 ]*oMatrix.m_afElement[4 ]
      + temp.m_afElement[5 ]*oMatrix.m_afElement[5 ]
      + temp.m_afElement[9 ]*oMatrix.m_afElement[6 ]
      + temp.m_afElement[13]*oMatrix.m_afElement[7 ];
   
   m_afElement[6] = temp.m_afElement[2 ]*oMatrix.m_afElement[4 ]
      + temp.m_afElement[6 ]*oMatrix.m_afElement[5 ]
      + temp.m_afElement[10]*oMatrix.m_afElement[6 ]
      + temp.m_afElement[14]*oMatrix.m_afElement[7 ];

   m_afElement[7] = temp.m_afElement[3 ]*oMatrix.m_afElement[4 ]
      + temp.m_afElement[7 ]*oMatrix.m_afElement[5 ]
      + temp.m_afElement[11]*oMatrix.m_afElement[6 ]
      + temp.m_afElement[15]*oMatrix.m_afElement[7 ];
   
   m_afElement[8] = temp.m_afElement[0 ]*oMatrix.m_afElement[8 ]
      + temp.m_afElement[4 ]*oMatrix.m_afElement[9 ]
      + temp.m_afElement[8 ]*oMatrix.m_afElement[10]
      + temp.m_afElement[12]*oMatrix.m_afElement[11];
   
   m_afElement[9] = temp.m_afElement[1 ]*oMatrix.m_afElement[8 ]
      + temp.m_afElement[5 ]*oMatrix.m_afElement[9 ]
      + temp.m_afElement[9 ]*oMatrix.m_afElement[10]
      + temp.m_afElement[13]*oMatrix.m_afElement[11];
   
   m_afElement[10]= temp.m_afElement[2 ]*oMatrix.m_afElement[8 ]
      + temp.m_afElement[6 ]*oMatrix.m_afElement[9 ]
      + temp.m_afElement[10]*oMatrix.m_afElement[10]
      + temp.m_afElement[14]*oMatrix.m_afElement[11];
   
   m_afElement[11]= temp.m_afElement[3 ]*oMatrix.m_afElement[8 ]
      + temp.m_afElement[7 ]*oMatrix.m_afElement[9 ]
      + temp.m_afElement[11]*oMatrix.m_afElement[10]
      + temp.m_afElement[15]*oMatrix.m_afElement[11];
   
   m_afElement[12]= temp.m_afElement[0 ]*oMatrix.m_afElement[12]
      + temp.m_afElement[4 ]*oMatrix.m_afElement[13]
      + temp.m_afElement[8 ]*oMatrix.m_afElement[14]
      + temp.m_afElement[12]*oMatrix.m_afElement[15];
   
   m_afElement[13]= temp.m_afElement[1 ]*oMatrix.m_afElement[12]
      + temp.m_afElement[5 ]*oMatrix.m_afElement[13]
      + temp.m_afElement[9 ]*oMatrix.m_afElement[14]
      + temp.m_afElement[13]*oMatrix.m_afElement[15];
   
   m_afElement[14]= temp.m_afElement[2 ]*oMatrix.m_afElement[12]
      + temp.m_afElement[6 ]*oMatrix.m_afElement[13]
      + temp.m_afElement[10]*oMatrix.m_afElement[14]
      + temp.m_afElement[14]*oMatrix.m_afElement[15];
   
   m_afElement[15]= temp.m_afElement[3 ]*oMatrix.m_afElement[12]
      + temp.m_afElement[7 ]*oMatrix.m_afElement[13]
      + temp.m_afElement[11]*oMatrix.m_afElement[14]
      + temp.m_afElement[15]*oMatrix.m_afElement[15];
   return *this;
}

CMatrix CMatrix::operator*(const CMatrix& oMatrix)
{
   CMatrix matResult(*this);
   matResult *= oMatrix;
   return matResult;
}

CVector3 CMatrix::operator*(const CVector3& v)
{
   CVector3 temp;
   
   temp.X() = m_afElement[0] * v.X() +
      m_afElement[4] * v.Y() +
      m_afElement[8] * v.Z();
   
   temp.Y() = m_afElement[1] * v.X() +
      m_afElement[5] * v.Y() +
      m_afElement[9] * v.Z();
   
   temp.Z() = m_afElement[2] * v.X() +
      m_afElement[6] * v.Y() +
      m_afElement[10] * v.Z();
   
   return temp;
}

void CMatrix::invert()
{
   float temp;

   temp = m_afElement[4 ];
   m_afElement[4 ] = m_afElement[1 ];
   m_afElement[1 ] = temp;

   temp = m_afElement[8 ];
   m_afElement[8 ] = m_afElement[2 ];
   m_afElement[2 ] = temp;

   temp = m_afElement[6 ];
   m_afElement[6 ] = m_afElement[9 ];
   m_afElement[9 ] = temp;
   
   m_afElement[12] = -m_afElement[12];
   m_afElement[13] = -m_afElement[13];
   m_afElement[14] = -m_afElement[14];
}
