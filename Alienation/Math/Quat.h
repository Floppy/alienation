// CQuat Class
#ifndef _QUAT_H
#define _QUAT_H

#include "config.h"

#include "Vector.h"

class CQuat
{
	public:
  		CQuat(float m_fx = 0, float m_fy = 0, float m_fz = 0, float m_fw = 1);

		void reset();
		void copyQuat(CQuat quaQ);
		void set(float fsx, float fsy, float fsz, float fsw) {m_fx = fsx, m_fy = fsy, m_fz = fsz, m_fw = fsw;}
		void axisAngleToQuat(CVector3 vecAxis, float fTheta);
  		void eulerToQuat(float fPitch, float fYaw, float fRoll);
		void normaliseQuat();
		float magnitudeQuat();
		void multQuat(CQuat quaQ);
		void conjugate() {m_fx = -m_fx, m_fy = -m_fy, m_fz = -m_fz;}

		float m_fx;
		float m_fy;
		float m_fz;
		float m_fw;
};
#endif

