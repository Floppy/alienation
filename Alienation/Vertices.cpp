// Vertices.cpp: implementation of the CVertices class.
//
//////////////////////////////////////////////////////////////////////

#include "Vertices.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVertices::CVertices()
{

}

CVertices::CVertices(float fNew_x, float fNew_y, float fNew_z)
{
	m_fx = fNew_x; m_fy = fNew_y; m_fz = fNew_z;

}

CVertices::~CVertices()
{

}

	// overload + operator so that we easier can add vectors
CVertices CVertices::operator+(CVertices oVert)
	{return CVertices(oVert.m_fx+m_fx, oVert.m_fy+m_fy, oVert.m_fz+m_fz);}
	// overload - operator that we easier can subtract vectors
CVertices CVertices::operator-(CVertices oVert) 
	{return CVertices(m_fx-oVert.m_fx, m_fy-oVert.m_fy, m_fz-oVert.m_fz);}
	// overload * operator that we easier can multiply by scalars
CVertices CVertices::operator*(float fNumber)	 
	{return CVertices(m_fx*fNumber, m_fy*fNumber, m_fz*fNumber);}
	// overload / operator that we easier can divide by a scalar
CVertices CVertices::operator/(float fNumber)	 
	{return CVertices(m_fx/fNumber, m_fy/fNumber, m_fz/fNumber);}
