// TCPServer.h: interface for the CTCPServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPSERVER_H__0CF9A002_310D_40AE_A563_375AB6C75DEB__INCLUDED_)
#define AFX_TCPSERVER_H__0CF9A002_310D_40AE_A563_375AB6C75DEB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "SDL.h"
#include "SDL_net.h"
#include "TCPPacket.h"
#include "UDPPacket.h"

class CTCPServer  
{
public:
   CTCPPacket * listen(Uint32 uiTimeout);
   CTCPServer();
   virtual ~CTCPServer();
private:
   TCPsocket m_oSocket; 
};

extern CTCPServer go_TCPServer;

#endif // !defined(AFX_TCPSERVER_H__0CF9A002_310D_40AE_A563_375AB6C75DEB__INCLUDED_)
