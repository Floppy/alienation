// Equipment.h: interface for the CEquipment class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUIPMENT_H__550D1F90_3DF6_487D_B337_C9EBCD8C8F22__INCLUDED_)
#define AFX_EQUIPMENT_H__550D1F90_3DF6_487D_B337_C9EBCD8C8F22__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Game/GameObject.h"
#include "GUI/Frame.h"

class CEquipment : public CFrame,
				   public CGameObject 
{
public:
	void setEquipmentName(const char * strName);
	char * getEquipmentName();
	CEquipment(int iNum, float fMass);
	CEquipment();
	virtual ~CEquipment();

private:
	char * m_strEquipmentName;
};

#endif // !defined(AFX_EQUIPMENT_H__550D1F90_3DF6_487D_B337_C9EBCD8C8F22__INCLUDED_)
