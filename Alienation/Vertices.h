// Vertices.h: interface for the CVertices class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VERTICES_H__A37EE639_6526_46C6_B634_779A497B166C__INCLUDED_)
#define AFX_VERTICES_H__A37EE639_6526_46C6_B634_779A497B166C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
  #include <windows.h>
#endif

#include <GL/gl.h>			// Header File For The OpenGL32 Library

class CVertices  
{
public:
	GLfloat m_fx, m_fy, m_fz;

	
	CVertices();
	CVertices(float fNew_x, float fNew_y, float fNew_z);
	virtual ~CVertices();
	// overload + operator so that we easier can add vectors
	CVertices operator+(CVertices oVert);
	// overload - operator that we easier can subtract vectors
	CVertices operator-(CVertices oVert);
	// overload * operator that we easier can multiply by scalars
	CVertices operator*(float fNumber);
	// overload / operator that we easier can divide by a scalar
	CVertices operator/(float fNumber);

};

#endif // !defined(AFX_VERTICES_H__A37EE639_6526_46C6_B634_779A497B166C__INCLUDED_)
