// UDPPacket.h: interface for the CUDPPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDPPACKET_H__387C01F1_F336_4D23_971E_94CE11218207__INCLUDED_)
#define AFX_UDPPACKET_H__387C01F1_F336_4D23_971E_94CE11218207__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Packet.h"
using namespace std;

class CUDPPacket : public CPacket  
{
public:
	UDPpacket * getData();
	void setData(const char * poData);
	bool sendAll();
	CUDPPacket();
	virtual ~CUDPPacket();
private:
	UDPpacket *m_strData;
};

#endif // !defined(AFX_UDPPACKET_H__387C01F1_F336_4D23_971E_94CE11218207__INCLUDED_)
