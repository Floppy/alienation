// Light.h: interface for the CLight class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIGHT_H__D6293CB0_7C45_4981_8977_EA3FA1933788__INCLUDED_)
#define AFX_LIGHT_H__D6293CB0_7C45_4981_8977_EA3FA1933788__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>


//Class to represent lighting. Needs far more work, but again, should be easy to expand
class CLight  
{
public:
	void update(GLenum light, GLenum type, float afAmount[4]);
	CLight();
	virtual ~CLight();
	void init(float afAmbient[4], float afDiffuse[4], float afPosition[4], GLenum light);

	float m_afLightAmbient[4];
	float m_afLightPosition[4];
	float m_afLightDiffuse[4];

};

#endif // !defined(AFX_LIGHT_H__D6293CB0_7C45_4981_8977_EA3FA1933788__INCLUDED_)
