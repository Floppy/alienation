// Shield.cpp: implementation of the CShield class.
//
//////////////////////////////////////////////////////////////////////

#include "Shield.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CShield::CShield()
{

}

CShield::~CShield()
{

}

int CShield::getShieldType()
{
   return m_iShieldType;
}

void CShield::setShieldType(int iType)
{
   m_iShieldType = iType;
}