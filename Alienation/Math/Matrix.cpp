#include "Math/Matrix.h"

CMatrix::CMatrix()
{
	LoadIdentity();
}

CMatrix::~CMatrix()
{
}

void CMatrix::LoadIdentity()
{
		m_afElement[0]=1.0f;
    	m_afElement[1]=0.0f;
    	m_afElement[2]=0.0f;
    	m_afElement[3]=0.0f;

    	m_afElement[4]=0.0f;
    	m_afElement[5]=1.0f;
    	m_afElement[6]=0.0f;
    	m_afElement[7]=0.0f;

    	m_afElement[8]=0.0f;
    	m_afElement[9]=0.0f;
    	m_afElement[10]=1.0f;
    	m_afElement[11]=0.0f;

    	m_afElement[12]=0.0f;
    	m_afElement[13]=0.0f;
    	m_afElement[14]=0.0f;
    	m_afElement[15]=1.0f;
}

void CMatrix::CopyMatrix(float m[16])
{
    	m_afElement[0 ] = m[0 ];
    	m_afElement[1 ] = m[1 ];
    	m_afElement[2 ] = m[2 ];
    	m_afElement[3 ] = m[3 ];
    	m_afElement[4 ] = m[4 ];
    	m_afElement[5 ] = m[5 ];
    	m_afElement[6 ] = m[6 ];
    	m_afElement[7 ] = m[7 ];
    	m_afElement[8 ] = m[8 ];
    	m_afElement[9 ] = m[9 ];
    	m_afElement[10] = m[10];
    	m_afElement[11] = m[11];
    	m_afElement[12] = m[12];
    	m_afElement[13] = m[13];
    	m_afElement[14] = m[14];
    	m_afElement[15] = m[15];
}

void CMatrix::CopyMatrixOut(float m[16])
{
    	m[0] = m_afElement[0 ];
    	m[1] = m_afElement[1 ];
    	m[2] = m_afElement[2 ];
    	m[3] = m_afElement[3 ];
    	m[4] = m_afElement[4 ];
    	m[5] = m_afElement[5 ];
    	m[6] = m_afElement[6 ];
    	m[7] = m_afElement[7 ];
    	m[8] = m_afElement[8 ];
    	m[9] = m_afElement[9 ];
    	m[10] = m_afElement[10];
    	m[11] = m_afElement[11];
    	m[12] = m_afElement[12];
    	m[13] = m_afElement[13];
    	m[14] = m_afElement[14];
    	m[15] = m_afElement[15];
}

void CMatrix::MultMatrix(float m[])
{
    	CMatrix temp;

    	temp.CopyMatrix(this->m_afElement);

  	m_afElement[0] = temp.m_afElement[0 ]*m[0 ]
        	+ temp.m_afElement[4 ]*m[1 ]
        	+ temp.m_afElement[8 ]*m[2 ]
        	+ temp.m_afElement[12]*m[3 ];

  	m_afElement[1] = temp.m_afElement[1 ]*m[0 ]
        	+ temp.m_afElement[5 ]*m[1 ]
        	+ temp.m_afElement[9 ]*m[2 ]
        	+ temp.m_afElement[13]*m[3 ];

  	m_afElement[2] = temp.m_afElement[2 ]*m[0 ]
       		+ temp.m_afElement[6 ]*m[1 ]
       		+ temp.m_afElement[10]*m[2 ]
       		+ temp.m_afElement[14]*m[3 ];

	m_afElement[3] = temp.m_afElement[3 ]*m[0 ]
       		+ temp.m_afElement[7 ]*m[1 ]
       		+ temp.m_afElement[11]*m[2 ]
       		+ temp.m_afElement[15]*m[3 ];

  	m_afElement[4] = temp.m_afElement[0 ]*m[4 ]
       		+ temp.m_afElement[4 ]*m[5 ]
       		+ temp.m_afElement[8 ]*m[6 ]
       		+ temp.m_afElement[12]*m[7 ];

  	m_afElement[5] = temp.m_afElement[1 ]*m[4 ]
       		+ temp.m_afElement[5 ]*m[5 ]
       		+ temp.m_afElement[9 ]*m[6 ]
       		+ temp.m_afElement[13]*m[7 ];

  	m_afElement[6] = temp.m_afElement[2 ]*m[4 ]
       		+ temp.m_afElement[6 ]*m[5 ]
       		+ temp.m_afElement[10]*m[6 ]
       		+ temp.m_afElement[14]*m[7 ];

  	m_afElement[7] = temp.m_afElement[3 ]*m[4 ]
       		+ temp.m_afElement[7 ]*m[5 ]
       		+ temp.m_afElement[11]*m[6 ]
       		+ temp.m_afElement[15]*m[7 ];

  	m_afElement[8] = temp.m_afElement[0 ]*m[8 ]
       		+ temp.m_afElement[4 ]*m[9 ]
       		+ temp.m_afElement[8 ]*m[10]
       		+ temp.m_afElement[12]*m[11];

  	m_afElement[9] = temp.m_afElement[1 ]*m[8 ]
       		+ temp.m_afElement[5 ]*m[9 ]
       		+ temp.m_afElement[9 ]*m[10]
       		+ temp.m_afElement[13]*m[11];

  	m_afElement[10]= temp.m_afElement[2 ]*m[8 ]
       		+ temp.m_afElement[6 ]*m[9 ]
       		+ temp.m_afElement[10]*m[10]
       		+ temp.m_afElement[14]*m[11];

  	m_afElement[11]= temp.m_afElement[3 ]*m[8 ]
       		+ temp.m_afElement[7 ]*m[9 ]
       		+ temp.m_afElement[11]*m[10]
       		+ temp.m_afElement[15]*m[11];

  	m_afElement[12]= temp.m_afElement[0 ]*m[12]
       		+ temp.m_afElement[4 ]*m[13]
       		+ temp.m_afElement[8 ]*m[14]
       		+ temp.m_afElement[12]*m[15];

  	m_afElement[13]= temp.m_afElement[1 ]*m[12]
       		+ temp.m_afElement[5 ]*m[13]
       		+ temp.m_afElement[9 ]*m[14]
       		+ temp.m_afElement[13]*m[15];

  	m_afElement[14]= temp.m_afElement[2 ]*m[12]
       		+ temp.m_afElement[6 ]*m[13]
       		+ temp.m_afElement[10]*m[14]
       		+ temp.m_afElement[14]*m[15];

  	m_afElement[15]= temp.m_afElement[3 ]*m[12]
       		+ temp.m_afElement[7 ]*m[13]
       		+ temp.m_afElement[11]*m[14]
       		+ temp.m_afElement[15]*m[15];
}

void CMatrix::MatrixInverse()
 {
  	CMatrix temp;

  	temp.CopyMatrix(this->m_afElement);

  	m_afElement[0 ] = temp.m_afElement[0 ];
  	m_afElement[1 ] = temp.m_afElement[4 ];
  	m_afElement[2 ] = temp.m_afElement[8 ];

  	m_afElement[4 ] = temp.m_afElement[1 ];
  	m_afElement[5 ] = temp.m_afElement[5 ];
  	m_afElement[6 ] = temp.m_afElement[9 ];

  	m_afElement[8 ] = temp.m_afElement[2 ];
  	m_afElement[9 ] = temp.m_afElement[6 ];
  	m_afElement[10] = temp.m_afElement[10];

  	m_afElement[12] *= -1.0f;
  	m_afElement[13] *= -1.0f;
  	m_afElement[14] *= -1.0f;
}

void CMatrix::MatrixFromAxisAngle(CVector3 axis, float theta)
{
        CQuat q;
        float halfTheta = theta * 0.5f;
        float cosHalfTheta = (float)cos(halfTheta);
        float sinHalfTheta = (float)sin(halfTheta);
        float xs, ys, zs, wx, wy, wz, xx, xy, xz, yy, yz, zz;
        q.m_fx = axis.m_fx * sinHalfTheta;
        q.m_fy = axis.m_fy * sinHalfTheta;
        q.m_fz = axis.m_fz * sinHalfTheta;
        q.m_fw = cosHalfTheta;
        xs = q.m_fx * 2;  ys = q.m_fy * 2;  zs = q.m_fz * 2;
        wx = q.m_fw * xs; wy = q.m_fw * ys; wz = q.m_fw * zs;
        xx = q.m_fx * xs; xy = q.m_fx * ys; xz = q.m_fx * zs;
        yy = q.m_fy * ys; yz = q.m_fy * zs; zz = q.m_fz * zs;
        m_afElement[0] = 1 - (yy + zz);
        m_afElement[1] = xy - wz;
        m_afElement[2] = xz + wy;
        m_afElement[4] = xy + wz;
        m_afElement[5] = 1 - (xx + zz);
        m_afElement[6] = yz - wx;
        m_afElement[8] = xz - wy;
        m_afElement[9] = yz + wx;
        m_afElement[10] = 1 - (xx + yy);
        m_afElement[12] = m_afElement[13] = m_afElement[14] = m_afElement[3] = m_afElement[7] = m_afElement[11] = 0;
        m_afElement[15] = 1;
}

void CMatrix::QuatToMatrix(CQuat quat)
{
  	float wx, wy, wz, xx, yy, yz, xy, xz, zz, x2, y2, z2;
  	// calculate coefficients
  	x2 = quat.m_fx + quat.m_fx;
  	y2 = quat.m_fy + quat.m_fy;
  	z2 = quat.m_fz + quat.m_fz;
  	xx = quat.m_fx * x2;
  	xy = quat.m_fx * y2;
  	xz = quat.m_fx * z2;
  	yy = quat.m_fy * y2;
  	yz = quat.m_fy * z2;
  	zz = quat.m_fz * z2;
  	wx = quat.m_fw * x2;
  	wy = quat.m_fw * y2;
  	wz = quat.m_fw * z2;
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

CVector3 CMatrix::MultMatrixVector(CVector3 v)
{
	CVector3 temp;

	temp.m_fx = m_afElement[0] * v.m_fx +
		m_afElement[4] * v.m_fy +
		m_afElement[8] * v.m_fz;

	temp.m_fy = m_afElement[1] * v.m_fx +
		m_afElement[5] * v.m_fy +
		m_afElement[9] * v.m_fz;

	temp.m_fz = m_afElement[2] * v.m_fx +
		m_afElement[6] * v.m_fy +
		m_afElement[10] * v.m_fz;

	return temp;
}

CMatrix CMatrix::operator * (CMatrix matM)
{
	CMatrix matResult;

	matResult.CopyMatrix(this->m_afElement);
	matResult.MultMatrix(matM.m_afElement);
	return matResult;
}

void CMatrix::operator = (CMatrix matM)
{
	this->CopyMatrix(matM.m_afElement);
}