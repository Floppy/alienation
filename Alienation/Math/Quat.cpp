#include "Math/Quat.h"
#include <math.h>


CQuat::CQuat() :
   m_fx(0),
   m_fy(0),
   m_fz(0),
   m_fw(1)
{}

CQuat::CQuat(float fx, float fy, float fz, float fw) :
   m_fx(fx),
   m_fy(fy),
   m_fz(fz),
   m_fw(fw)
{}

CQuat::CQuat(const CVector3& vecAxis, float fTheta)
{
   float halfTheta = fTheta * 0.5f;
   float cosHalfTheta = (float)cos(halfTheta);
   float sinHalfTheta = (float)sin(halfTheta);
   m_fx = vecAxis.X() * sinHalfTheta;
   m_fy = vecAxis.Y() * sinHalfTheta;
   m_fz = vecAxis.Z() * sinHalfTheta;
   m_fw = cosHalfTheta;
}

CQuat::CQuat(float pitch, float yaw, float roll)
{
   float cr, cp, cy, sr, sp, sy, cpcy, spsy;  // calculate trig identities
   cr = (float)cos(roll/2);
   cp = (float)cos(pitch/2);
   cy = (float)cos(yaw/2);
   sr = (float)sin(roll/2);
   sp = (float)sin(pitch/2);
   sy = (float)sin(yaw/2);
   cpcy = cp * cy;
   spsy = sp * sy;
   m_fw = cr * cpcy + sr * spsy;
   m_fx = sr * cpcy - cr * spsy;
   m_fy = cr * sp * cy + sr * cp * sy;
   m_fz = cr * cp * sy - sr * sp * cy;
}

CQuat::CQuat(const CQuat& oQuat) :
   m_fx(oQuat.m_fx),
   m_fy(oQuat.m_fy),
   m_fz(oQuat.m_fz),
   m_fw(oQuat.m_fw)
{}

void CQuat::loadIdentity()
{
   m_fx = 0.0;
   m_fy = 0.0;
   m_fz = 0.0;
   m_fw = 1.0;
}

CQuat& CQuat::operator=(const CQuat& oQuat)
{
   m_fx = oQuat.m_fx;
   m_fy = oQuat.m_fy;
   m_fz = oQuat.m_fz;
   m_fw = oQuat.m_fw;
   return *this;
}

CQuat& CQuat::operator*=(const CQuat& q)
{
   CVector3 vectorq1(m_fx,m_fy,m_fz);
   CVector3 vectorq2(q.m_fx,q.m_fy,q.m_fz);
   
   CVector3 tempvec1(vectorq1.cross(vectorq2));
   CVector3 tempvec2(vectorq2 * m_fw);
   CVector3 tempvec3(vectorq1 * q.m_fw);
   
   m_fx = tempvec1.X() + tempvec2.X() + tempvec3.X();
   m_fy = tempvec1.Y() + tempvec2.Y() + tempvec3.Y();
   m_fz = tempvec1.Z() + tempvec2.Z() + tempvec3.Z();
   m_fw = (m_fw*q.m_fw) - vectorq1.dot(vectorq2);
   
   return *this;
}

void CQuat::set(float fx, float fy, float fz, float fw) {
   m_fx = fx;
   m_fy = fy;
   m_fz = fz;
   m_fw = fw;
}

void CQuat::normalise()
{
   float Mag(magnitude());
   m_fw /= Mag;
   m_fx /= Mag;
   m_fy /= Mag;
   m_fz /= Mag;
}

float CQuat::magnitude()
{
   return( (float)sqrt(m_fw*m_fw + m_fx*m_fx + m_fy*m_fy + m_fz*m_fz));
}


