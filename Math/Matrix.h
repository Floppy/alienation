#ifndef _MATRIX_H
#define _MATRIX_H

#include "config.h"

#include "Math/Quat.h"
#include "Math/Vector.h"

#include <SDL_opengl.h>

namespace NSDMath {

   /**
    * A 4x4 Matrix.
    * Suitable for homogenous transforms and the like.
    */
   class CMatrix
   {

   public:
	   void setElement(int iIndex, float fValue);
   
      /** 
       * Default Constructor.
       * Creates an identity matrix.
       */ 
      CMatrix();

      /** 
       * Constructor from axis and angle.
       * @param vecAxis Axis to rotate around.
       * @param fAngle Angle to rotate in radians.
       */ 
      CMatrix(const CVector3& vecAxis, float fAngle);

      /**
       * Constructor from Quaternion.
       */
      CMatrix(const CQuat& quat);

      /**
       * Constructor from OpenGL matrix.
       * Fetches a matrix from OpenGL.
       * @param glMatrix A GLenum identifying a GL matrix. For instance, GL_PROJECTION_MATRIX, or GL_MODELVIEW_MATRIX.
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

}
#endif //_MATRIX_H

