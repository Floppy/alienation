#include "Math/Quat.h"
#include <math.h>


CQuat::CQuat(float fsx, float fsy, float fsz, float fsw) :
	m_fx(fsx),
	m_fy(fsy),
	m_fz(fsz),
	m_fw(fsw)
{}


void CQuat::reset()
{
	m_fx = 0.0;
	m_fy = 0.0;
	m_fz = 0.0;
	m_fw = 1.0;
}

void CQuat::copyQuat(CQuat q)
{
	m_fx = q.m_fx;
	m_fy = q.m_fy;
	m_fz = q.m_fz;
	m_fw = q.m_fw;
}

void CQuat::axisAngleToQuat(CVector3 axis, float theta)
{
	float halfTheta = theta * 0.5f;
	float cosHalfTheta = (float)cos(halfTheta);
	float sinHalfTheta = (float)sin(halfTheta);
	m_fx = axis.X() * sinHalfTheta;
	m_fy = axis.Y() * sinHalfTheta;
	m_fz = axis.Z() * sinHalfTheta;
	m_fw = cosHalfTheta;
}

void CQuat::eulerToQuat(float pitch, float yaw, float roll)
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

float CQuat::magnitudeQuat()
{
	return( (float)sqrt(m_fw*m_fw + m_fx*m_fx + m_fy*m_fy + m_fz*m_fz));
}

void CQuat::normaliseQuat()
{
	float Mag;
	Mag = magnitudeQuat();
	m_fw = m_fw/Mag;
	m_fx = m_fx/Mag;
	m_fy = m_fy/Mag;
	m_fz = m_fz/Mag;
}

void CQuat::multQuat(CQuat q)
{
	CQuat q3;
	CVector3 vectorq1(m_fx,m_fy,m_fz);
	CVector3 vectorq2(q.m_fx,q.m_fy,q.m_fz);

	CVector3 tempvec1;
	tempvec1 = vectorq1;
	q3.m_fw = (m_fw*q.m_fw) - tempvec1.dot(vectorq2);
	tempvec1 = tempvec1.cross(vectorq2);

	CVector3 tempvec2(vectorq2 * m_fw);
	CVector3 tempvec3(vectorq1 * q.m_fw);

	q3.m_fx = tempvec1.X() + tempvec2.X() + tempvec3.X();
	q3.m_fy = tempvec1.Y() + tempvec2.Y() + tempvec3.Y();
	q3.m_fz = tempvec1.Z() + tempvec2.Z() + tempvec3.Z();
	copyQuat(q3);
}
