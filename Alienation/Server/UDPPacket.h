// UDPPacket.h: interface for the CUDPPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDPPACKET_H__387C01F1_F336_4D23_971E_94CE11218207__INCLUDED_)
#define AFX_UDPPACKET_H__387C01F1_F336_4D23_971E_94CE11218207__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Packet.h"
#include <string.h>

using namespace std;

class CUDPPacket : public CPacket  
{
public:
	void getMessageData(char * strUsername, char * strMessage);
	int getLastMessageRecievedType();
	void setLastMessageRecievedType(int iLastMessage);
	int recieve(UDPsocket oSocket);
	void send(UDPsocket poSocket, int iMessageType);
	void setData(char *strUser, char *strMessage);
	char * getData();
	void setData(char * poData);
	CUDPPacket();
	virtual ~CUDPPacket();
private:
	struct sMessage
	{
		int iId;
		char strUser[32];
		char strMessage[512];
	};
	sMessage * m_poMessage;
	int m_iLastMessageRecievedType;
};

#endif // !defined(AFX_UDPPACKET_H__387C01F1_F336_4D23_971E_94CE11218207__INCLUDED_)
