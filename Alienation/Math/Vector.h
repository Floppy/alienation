#ifndef _VECTOR_H
#define _VECTOR_H

#include "config.h"

#include <math.h>

namespace NSDMath {

   /**
    * A 2D vector
    */
   class CVector2 
   {

   public:
   
      /**
       * Constructor.
       * Does not set to zero by default, for efficiency.
       */
      CVector2()
         {}
   
      /**
       * Constructor.
       * Sets the value of the vector
       * @param fx X value
       * @param fy Y value
       */
      CVector2(float fx, float fy)
         {
            m_oVector[0] = fx;
            m_oVector[1] = fy;
         }
   
      /**
       * Assignment operator.
       * Copies the value of the passed vector into this.
       * @param vecV Vector to be copied.
       * @return Reference to this vector
       */
      CVector2& operator=(const CVector2& vecV)
         {
            m_oVector[0] = vecV.m_oVector[0];
            m_oVector[1] = vecV.m_oVector[1];
            return *this;
         }

      /**
       * X Component.
       * @return Reference to X component of vector.
       */
      float& X() 
         { return m_oVector[0]; }

      /**
       * X Component.
       * @return X component of vector.
       */
      float X() const
         { return m_oVector[0]; }

      /**
       * Y Component.
       * @return Reference to Y component of vector.
       */
      float& Y() 
         { return m_oVector[1]; }
      /**
       * Y Component.
       * @return Y component of vector.
       */
      float Y() const
         { return m_oVector[1]; }

      /**
       * Array access.
       * @return An array suitable for using directly with glXxx2fv functions.
       */ 
      const float* glVector() const
         { return m_oVector; }

   protected:

      /** 
       * Vector components
       */
      float m_oVector[2];

   };

   /**
    * A 3D vector
    */
   class CVector3
   {

   public:

      /**
       * Constructor.
       * Does not set to zero by default, for efficiency.
       */
      CVector3()
         {}
   
      /**
       * Constructor.
       * Sets the value of the vector
       * @param fx X value
       * @param fy Y value
       * @param fz Z value
       */
      CVector3(float fx, float fy, float fz)
         {
            m_oVector[0] = fx;
            m_oVector[1] = fy;
            m_oVector[2] = fz;
         }
   
      /**
       * Assignment operator.
       * Copies the value of the passed vector into this.
       * @param vecV Vector to be copied.
       * @return Reference to this vector
       */
      CVector3& operator=(const CVector3& vecV)
         {
            m_oVector[0] = vecV.m_oVector[0];
            m_oVector[1] = vecV.m_oVector[1];
            m_oVector[2] = vecV.m_oVector[2];
            return *this;
         }

      /**
       * X Component.
       * @return Reference to X component of vector.
       */
      float& X() 
         { return m_oVector[0]; }

      /**
       * X Component.
       * @return X component of vector.
       */
      float X() const
         { return m_oVector[0]; }

      /**
       * Y Component.
       * @return Reference to Y component of vector.
       */
      float& Y() 
         { return m_oVector[1]; }

      /**
       * Y Component.
       * @return Y component of vector.
       */
      float Y() const
         { return m_oVector[1]; }

      /**
       * Z Component.
       * @return Reference to Z component of vector.
       */
      float& Z() 
         { return m_oVector[2]; }

      /**
       * Z Component.
       * @return Z component of vector.
       */
      float Z() const
         { return m_oVector[2]; }

      /**
       * Array access.
       * @return An array suitable for using directly with glXxx3fv functions.
       */ 
      const float* glVector() const
         { return m_oVector; }

   
      /**
       * Equality operator.
       * @param vecV The vector to compare to this one.
       * @return true if the vectors are exactly equal
       */ 
      bool operator==(const CVector3& vecV)
         {
            return (m_oVector[0] == vecV.m_oVector[0] &&
                    m_oVector[1] == vecV.m_oVector[1] &&
                    m_oVector[2] == vecV.m_oVector[2]);
         }

      /**
       * Vector addition.
       * @param vecV The vector to add to this one.
       * @return A new vector equal to this + vecV
       */ 
      CVector3 operator+(const CVector3& vecV) const
         {
            return CVector3(m_oVector[0] + vecV.m_oVector[0], m_oVector[1] + vecV.m_oVector[1], m_oVector[2] + vecV.m_oVector[2]);
         }

      /**
       * Vector addition.
       * Modifies this : this = this + vecV;
       * @param vecV The vector to add to this one.
       * @return A reference to this object.
       */ 
      CVector3& operator+=(const CVector3& vecV)
         {
            m_oVector[0] += vecV.m_oVector[0];
            m_oVector[1] += vecV.m_oVector[1];
            m_oVector[2] += vecV.m_oVector[2];
            return *this;
         }

      /**
       * Vector subtraction.
       * @param vecV The vector to subtract from this one.
       * @return A new vector equal to this - vecV
       */ 
      CVector3 operator-(const CVector3& vecV) const
         {
            return CVector3(m_oVector[0] - vecV.m_oVector[0], m_oVector[1] - vecV.m_oVector[1], m_oVector[2] - vecV.m_oVector[2]);
         }

      /**
       * Vector subtraction.
       * Modifies this : this = this - vecV;
       * @param vecV The vector to subtract from this one.
       * @return A reference to this object.
       */ 
      CVector3& operator-=(const CVector3& vecV)
         {
            m_oVector[0] -= vecV.m_oVector[0];
            m_oVector[1] -= vecV.m_oVector[1];
            m_oVector[2] -= vecV.m_oVector[2];
            return *this;
         }

      /**
       * Multiplication by scalar value.
       * @return A new vector equal to this * fValue.
       */ 
      CVector3 operator*(float fValue) const
         {
            return CVector3(m_oVector[0] * fValue, m_oVector[1] * fValue, m_oVector[2] * fValue);
         }

      /**
       * Multiplication by scalar value.
       * Modifies this : this = this * fValue;
       * @return A reference to this object.
       */ 
      CVector3& operator*=(float fValue)
         {
            m_oVector[0] *= fValue;
            m_oVector[1] *= fValue;
            m_oVector[2] *= fValue;
            return *this;
         }

      /**
       * Multiplication by vector value.
       * @return A new vector equal to this * vecValue.
       */ 
      CVector3 operator*(CVector3 vecValue) const
         {
            return CVector3(m_oVector[0] * vecValue.m_oVector[0], 
                            m_oVector[1] * vecValue.m_oVector[1],
                            m_oVector[2] * vecValue.m_oVector[2]);
         }

      /**
       * Multiplication by vector value.
       * Modifies this : this = this * vecValue;
       * @return A reference to this object.
       */ 
      CVector3& operator*=(CVector3 vecValue)
         {
            m_oVector[0] *= vecValue.m_oVector[0];
            m_oVector[1] *= vecValue.m_oVector[1];
            m_oVector[2] *= vecValue.m_oVector[2];
            return *this;
         }

      /**
       * Division by scalar value.
       * @return A new vector equal to this / fValue.
       */ 
      CVector3 operator/(float fValue) const
         {
            return CVector3(m_oVector[0] / fValue, m_oVector[1] / fValue, m_oVector[2] / fValue);
         }

      /**
       * Division by scalar value.
       * Modifies this : this = this / fValue;
       * @return A reference to this object.
       */ 
      CVector3& operator/=(float fValue)
         {
            m_oVector[0] /= fValue;
            m_oVector[1] /= fValue;
            m_oVector[2] /= fValue;
            return *this;
         }

      /**
       * Negation.
       * All components are negated.
       * @return A new vector which is the inverse of this one.
       */ 
      CVector3 operator-() const
         {
            return CVector3(-m_oVector[0], -m_oVector[1], -m_oVector[2]);
         }

      /**
       * Dot product.
       * @param vecV The vector to take the dot product with.
       * @return The dot or scalar product of this and vecV.
       */
      float dot(const CVector3& vecV) const
         {
            return m_oVector[0] * vecV.m_oVector[0] + m_oVector[1] * vecV.m_oVector[1] + m_oVector[2] * vecV.m_oVector[2];
         }

      /**
       * Cross product.
       * @param vecV The vector to take the cross product with.
       * @return A new vector containing the cross or vector product of this and vecV.
       */
      CVector3 cross(const CVector3& vecV) const
         {
            CVector3 vecNormal;									
            vecNormal.m_oVector[0] = ((m_oVector[1] * vecV.m_oVector[2]) - (m_oVector[2] * vecV.m_oVector[1]));
            vecNormal.m_oVector[1] = ((m_oVector[2] * vecV.m_oVector[0]) - (m_oVector[0] * vecV.m_oVector[2]));
            vecNormal.m_oVector[2] = ((m_oVector[0] * vecV.m_oVector[1]) - (m_oVector[1] * vecV.m_oVector[0]));      
            return vecNormal;
         }
   
      /**
       * Vector magnitude.
       * @return The length of this vector.
       */
      float length() const
         {
            return static_cast<float>(sqrt(m_oVector[0]*m_oVector[0] + m_oVector[1]*m_oVector[1] + m_oVector[2]*m_oVector[2]));
         }

      /**
       * Make a unit vector.
       * @return A new vector which has the same direction as this one, but unit length.
       */
      CVector3 unit() const
         {
            // Copy this vector
            CVector3 vecNew(*this);
            // Make unit length
            vecNew.normalise();
            // Done
            return vecNew;
         }

      /**
       * Normalise this vector.
       * Does not change this vector's direction, but makes it's length 1.
       */
      void normalise()
         {
            // Get length
            float fLength = this->length();
            // Check for divide-by-zero
            if (fLength == 0) return;
            // Scale
            (*this) /= fLength;
         }

      /**
       * Angle between two vectors.
       * @param vec The vector to compare to.
       * @return The angle between the two in radians, between 0 and PI.
       */
      float angle(const CVector3& vec) const
         {
            return static_cast<float>(acos(this->dot(vec) / (length() * vec.length())));
         }

   protected:

      /** 
       * Vector components
       */
      float m_oVector[3];
        
   };

}

#endif

   
