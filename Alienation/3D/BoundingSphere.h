// BoundingSphere.h: interface for the CBoundingSphere class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BOUNDINGSPHERE_H__07570A6B_3C9C_4041_BB41_023BE7D446F1__INCLUDED_)
#define AFX_BOUNDINGSPHERE_H__07570A6B_3C9C_4041_BB41_023BE7D446F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Math/Vector.h"

class CBoundingSphere  
{
public:
	CBoundingSphere();
	virtual ~CBoundingSphere();
	CVector3 m_vecPos; 
	float m_fRadius;
};

#endif // !defined(AFX_BOUNDINGSPHERE_H__07570A6B_3C9C_4041_BB41_023BE7D446F1__INCLUDED_)
