#include "quat.h"
#include "math.h"


CQuat::CQuat(float fsx, float fsy, float fsz, float fsw)
{
	m_fx = fsx;
	m_fy = fsy;
	m_fz = fsz;
	m_fw = fsw;
}


CQuat::~CQuat()
{
}

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
	m_fx = axis.m_fx * sinHalfTheta;
	m_fy = axis.m_fy * sinHalfTheta;
	m_fz = axis.m_fz * sinHalfTheta;
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
	CVector3 vectorq1;
	CVector3 vectorq2;
	vectorq1.m_fx = m_fx;
	vectorq1.m_fy = m_fy;
	vectorq1.m_fz = m_fz;
	vectorq2.m_fx = q.m_fx;
	vectorq2.m_fy = q.m_fy;
	vectorq2.m_fz = q.m_fz;

	CVector3 tempvec1;
	CVector3 tempvec2;
	CVector3 tempvec3;
	tempvec1 = vectorq1;
	q3.m_fw = (m_fw*q.m_fw) - tempvec1.dot(vectorq2);
	tempvec1 = tempvec1.cross(vectorq2);
	tempvec2.m_fx = m_fw * q.m_fx;
	tempvec2.m_fy = m_fw * q.m_fy;
	tempvec2.m_fz = m_fw * q.m_fz;
	tempvec3.m_fx = q.m_fw * m_fx;
	tempvec3.m_fy = q.m_fw * m_fy;
	tempvec3.m_fz = q.m_fw * m_fz;
	q3.m_fx = tempvec1.m_fx + tempvec2.m_fx + tempvec3.m_fx;
	q3.m_fy = tempvec1.m_fy + tempvec2.m_fy + tempvec3.m_fy;
	q3.m_fz = tempvec1.m_fz + tempvec2.m_fz + tempvec3.m_fz;
	copyQuat(q3);
}
