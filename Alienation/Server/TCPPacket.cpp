// TCPPacket.cpp: implementation of the CTCPPacket class.
//
//////////////////////////////////////////////////////////////////////

#include "TCPPacket.h"
#include <string.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTCPPacket::CTCPPacket()
{
   m_Data.iDataValue1 = 0;
   m_Data.iDataValue2 = 0;
   m_Data.lDataValue1 = 0l;
   m_Data.lDataValue2 = 0l;
   strcpy( m_Data.strMessage1, "");
   strcpy( m_Data.strMessage2, "");
}

CTCPPacket::~CTCPPacket()
{

}

bool CTCPPacket::sendAll()
{
   return true;
}

void CTCPPacket::getData(int *piData1, int *piData2, 
						 long *plData1, long *plData2, 
						 char *strMessage1, char *strMessage2)
{
	*piData1 = m_Data.iDataValue1;
	*piData2 = m_Data.iDataValue2;
	*plData1 = m_Data.lDataValue1;
	*plData2 = m_Data.lDataValue2;
	strcpy(strMessage1, m_Data.strMessage1);
	strcpy(strMessage2, m_Data.strMessage2);
}


void CTCPPacket::setData(int iData1, int iData2, 
						 long lData1, long lData2, 
						 const char *strMessage1, const char *strMessage2)
{
   m_Data.iDataValue1 = iData1;
   m_Data.iDataValue2 = iData2;
   m_Data.lDataValue1 = lData1;
   m_Data.lDataValue2 = lData2;
   strcpy( m_Data.strMessage1, strMessage1);
   strcpy( m_Data.strMessage2, strMessage2);
}
