#ifndef _QUAT_H
#define _QUAT_H

#include "config.h"
#include "Math/Vector.h"

/**
 * A Quaternion.
 * Quaternions represent 3D rotations.
 */
class CQuat
{
   
 public:
   
   /**
    * Default Constructor.
    * Creates identity quaternion.
    */
   CQuat();

   /**
    * Constructor from values.
    */
   CQuat(float m_fx, float m_fy, float m_fz, float m_fw);

   /**
    * Constructor from axis and angle.
    * @param vecAxis Axis to rotate around.
    * @param fAngle Angle to rotate in radians.
    */
   CQuat(const CVector3& vecAxis, float fAngle);

   /**
    * Constructor from Euler angles.
    * @param fYaw Rotation around Y axis.
    * @param fPitch Rotation around X axis.
    * @param fRoll Rotation around Z axis.
    */
   CQuat(float fPitch, float fYaw, float fRoll);

   /**
    * Copy constructor.
    */
   CQuat(const CQuat& oQuat);

   /**
    * Set this to the identity quaternion.
    */ 
   void loadIdentity();

   /**
    * Assignment.
    */   
   CQuat& operator=(const CQuat& oQuat);

   /**
    * Multiplication.
    * @bug I think something is backwards in here - tempvec1 should be vec2 x vec1, not the other way around. However, doing that breaks everything, so I've left it as is.
    */   
   CQuat& operator*=(const CQuat& oQuat);

   /**
    * Set values.
    */   
   void set(float fsx, float fsy, float fsz, float fsw);

   /**
    * Normalise.
    */   
   void normalise();

   /**
    * Magnitude.
    */   
   float magnitude();

   /**
    * Conjugate.
    * Make this quaternion into it's own inverse.
    */
   void conjugate() 
   {m_fx = -m_fx; m_fy = -m_fy; m_fz = -m_fz;}

   /**
    * X component
    */
   float X() const
   { return m_fx; }

   /**
    * Y component
    */
   float Y() const
   { return m_fy; }

   /**
    * Z component
    */
   float Z() const
   { return m_fz; }

   /**
    * W component
    */
   float W() const
   { return m_fw; }
   

 protected:

   /**
    * X component
    */
   float m_fx;

   /**
    * Y component
    */
   float m_fy;

   /**
    * Z component
    */
   float m_fz;

   /**
    * W component
    */
   float m_fw;

};

#endif // _QUAT_H

