// Packet.h: interface for the CPacket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PACKET_H__97235043_A504_4486_9CD5_21C5F5121C19__INCLUDED_)
#define AFX_PACKET_H__97235043_A504_4486_9CD5_21C5F5121C19__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDL_net.h"
#include "Client.h"

class CPacket  
{
public:

	virtual bool sendAll() = 0;
	CPacket();
	virtual ~CPacket();

};

#endif // !defined(AFX_PACKET_H__97235043_A504_4486_9CD5_21C5F5121C19__INCLUDED_)
