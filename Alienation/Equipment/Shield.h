// Shield.h: interface for the CShield class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SHIELD_H__526496BB_99F4_4109_8780_008DF56EC37D__INCLUDED_)
#define AFX_SHIELD_H__526496BB_99F4_4109_8780_008DF56EC37D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equipment/Equipment.h"

enum shieldType 
{
   SHIELD_FRONT,
   SHIELD_REAR,
   SHIELD_RIGHT,
   SHIELD_LEFT
};

class CShield : public CEquipment  
{
public:
	void setShieldType(int iType);
	int getShieldType();
	CShield();
	virtual ~CShield();

private:
	int m_iShieldType;
};

#endif // !defined(AFX_SHIELD_H__526496BB_99F4_4109_8780_008DF56EC37D__INCLUDED_)
