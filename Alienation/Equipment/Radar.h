// Radar.h: interface for the CRadar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RADAR_H__B2305CC7_9100_4FE5_911F_F1536522D58C__INCLUDED_)
#define AFX_RADAR_H__B2305CC7_9100_4FE5_911F_F1536522D58C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equipment/Equipment.h"

class CRadar : 
	public CEquipment
{
public:
	CRadar();
	virtual ~CRadar();

};

#endif // !defined(AFX_RADAR_H__B2305CC7_9100_4FE5_911F_F1536522D58C__INCLUDED_)
