// Matrix Class
#ifndef _MATRIX_H
#define _MATRIX_H

#include "config.h"

#include "quat.h"
#include "Physics1.h"
#include "vector.h"

//Matrix class from Aquas workspace. Need to add operator overloading
//Well, not NEED, but want to. Added one function which multiplies a 
//matrix by a vector 
class CMatrix
{
public:
	CMatrix();
	~CMatrix();

	void LoadIdentity();
	void CopyMatrix(float m[16]);
	void CopyMatrixOut(float m[16]);
	void MultMatrix(float m[16]);
	void operator *= (CMatrix matM);
	CMatrix operator * (CMatrix matM);
	CVector3 operator * (CVector3 vecV);
	void operator = (CMatrix matM);
	CVector3 MultMatrixVector(CVector3 v);
	void MatrixInverse(); 
	void MatrixFromAxisAngle(CVector3 axis, float theta);
	void QuatToMatrix(CQuat quat); 

	float m_afElement[16];
};
#endif

