// Equipment.cpp: implementation of the CEquipment class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/Equipment.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEquipment::CEquipment(int iNum, float fMass)
{
   CGameObject(iNum, fMass);
}

CEquipment::CEquipment()
{

}


CEquipment::~CEquipment()
{

}

char * CEquipment::getEquipmentName()
{
   return m_strEquipmentName;
}

void CEquipment::setEquipmentName(const char* strName)
{
   strcpy(m_strEquipmentName, strName);
}
