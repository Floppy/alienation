#ifndef _MATRIX_H
#define _MATRIX_H

#include "config.h"

#include "Math/Quat.h"
#include "Math/Vector.h"
#include <GL/gl.h>

//Matrix class from Aquas workspace. Need to add operator overloading
//Well, not NEED, but want to. Added one function which multiplies a 
//matrix by a vector 
/**
 * A 4x4 Matrix.
 * Suitable for homogenous transforms and the like.
 */
class CMatrix
{

 public:
   
   /** 
    * Default Constructor.
    * Creates an identity matrix.
    */ 
   CMatrix();

   /** 
    * Constructor from axis and angle.
    * @param oAxis Axis to rotate around.
    * @param oAngle Angle to rotate in radians.
    */ 
   CMatrix(const CVector3& vecAxis, float fTheta);

   /**
    * Constructor from Quaternion.
    */
   CMatrix(const CQuat& quat);

   /**
    * Constructor from OpenGL matrix.
    */
   CMatrix(GLenum glMatrix);

   /** 
    * Copy Constructor.
    */ 
   CMatrix(const CMatrix& oMatrix);

   /** 
    * Create an identity matrix.
    */ 
   void loadIdentity();

   /**
    * Copy matrix into float array.
    */
   void CopyMatrixOut(float m[16]);
   
   /** 
    * Assignment.
    */
   CMatrix& operator=(const CMatrix& oMatrix);

   /** 
    * Matrix Multiplication.
    */
   CMatrix& operator*=(const CMatrix& oMatrix);

   /** 
    * Matrix Multiplication.
    */
   CMatrix operator * (const CMatrix& oMatrix);

   /** 
    * Vector Multiplication.
    */
   CVector3 operator * (const CVector3& vecV);

   /** 
    * Invert matrix.
    */
   void invert(); 

   /** 
    * Element access.
    */
   float element(unsigned int uiElement) const
   { return m_afElement[uiElement]; }

   /** 
    * Element access.
    */
   float& element(unsigned int uiElement)
   { return m_afElement[uiElement]; }

   /** 
    * Element array access.
    * Suitable for use with glLoadMatrixf or similar.
    */
   const float* glElements() const
   { return m_afElement; }


 protected:

   float m_afElement[16];
   
};

#endif //_MATRIX_H

