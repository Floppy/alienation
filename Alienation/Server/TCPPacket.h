// TCPPacket.h: interface for the CTCPPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPPACKET_H__DD2EE73D_F5D9_4402_983E_016B2A626C11__INCLUDED_)
#define AFX_TCPPACKET_H__DD2EE73D_F5D9_4402_983E_016B2A626C11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDL.h"
#include "SDL_Net.h"
#include "Packet.h"

class CTCPPacket : public CPacket  
{
public:
	void getData(int *piData1, int *piData2, long *plData1, long *plData2, char *strMessage1, char *strMessage2);
	void setData(int iData1, int iData2, long lData1, long lData2, const char *strMessage1, const char *strMessage2);
	bool sendAll();
	CTCPPacket();
	virtual ~CTCPPacket();
private:
   
   TCPsocket m_oSocket;

   struct Data
   {
	  int  iDataValue1;
	  long lDataValue1;
	  int  iDataValue2;
	  long lDataValue2;
	  char strMessage1[256];
	  char strMessage2[256];
   } m_Data;
};

#endif // !defined(AFX_TCPPACKET_H__DD2EE73D_F5D9_4402_983E_016B2A626C11__INCLUDED_)
