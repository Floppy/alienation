// SpeedIndicator.cpp: implementation of the CSpeedIndicator class.
//
//////////////////////////////////////////////////////////////////////

#include "Equipment/SpeedIndicator.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSpeedIndicator::CSpeedIndicator()
{

}

CSpeedIndicator::~CSpeedIndicator()
{

}

void CSpeedIndicator::operator = (CSpeedIndicator * poSpeed)
{
 
}

void CSpeedIndicator::setSpeed(float fSpeed)
{
   m_fSpeed = fSpeed;
}

float CSpeedIndicator::getSpeed()
{
   return m_fSpeed;
}
