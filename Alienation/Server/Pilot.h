// Pilot.h: interface for the CPilot class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PILOT_H__2812F5F7_CC5C_496D_AFC6_A7CB89D2AF2E__INCLUDED_)
#define AFX_PILOT_H__2812F5F7_CC5C_496D_AFC6_A7CB89D2AF2E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#include <windows.h>
#endif

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

class CPilot  
{
public:
	bool findByPilotName(char * strPilotName);
	bool findByPrimaryKey(int iPrimaryKey);
	char * getPassword();
	CPilot();
	virtual ~CPilot();

private:
	char * m_strPassword;
	int m_iPilotID;
	char * m_strPilotName;
};

#endif // !defined(AFX_PILOT_H__2812F5F7_CC5C_496D_AFC6_A7CB89D2AF2E__INCLUDED_)
