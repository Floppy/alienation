// Frustrum.h: interface for the CFrustrum class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FRUSTRUM_H__BD8C075F_DCD0_4FA2_B46C_400800C1B596__INCLUDED_)
#define AFX_FRUSTRUM_H__BD8C075F_DCD0_4FA2_B46C_400800C1B596__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "3D/BoundingSphere.h"
	
using namespace NSDMath;

enum FrustumSide
{
	RIGHT	= 0,		// The RIGHT side of the frustum
	LEFT	= 1,		// The LEFT	 side of the frustum
	BOTTOM	= 2,		// The BOTTOM side of the frustum
	TOP		= 3,		// The TOP side of the frustum
	BACK	= 4,		// The BACK	side of the frustum
	FRONT	= 5			// The FRONT side of the frustum
}; 


// Like above, instead of saying a number for the ABC and D of the plane, we
// want to be more descriptive.
enum PlaneData
{
	A = 0,				// The X value of the plane's normal
	B = 1,				// The Y value of the plane's normal
	C = 2,				// The Z value of the plane's normal
	D = 3				// The distance the plane is from the origin
};


class CFrustum  
{
public:
	CFrustum();
	virtual ~CFrustum();
	// Call this every time the camera moves to update the frustum
	void CalculateFrustum();

	// This takes a 3D point and returns TRUE if it's inside of the frustum
	bool PointInFrustum(const CVector3& vecPoint);

	// This takes a 3D point and a radius and returns TRUE if the sphere is inside of the frustum
	bool SphereInFrustum(CBoundingSphere *poSphere);

	// This takes the center and half the length of the cube.
	bool CubeInFrustum(const CVector3& vecCentre, float size );

	void NormalizePlane(int side);



private:

	// This holds the A B C and D values for each side of our frustum.
	static float m_Frustum[6][4];

};

//float CFrustum::m_Frustum[6][4];

#endif // !defined(AFX_FRUSTRUM_H__BD8C075F_DCD0_4FA2_B46C_400800C1B596__INCLUDED_)

