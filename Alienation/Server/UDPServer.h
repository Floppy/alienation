// UDPServer.h: interface for the CUDPServer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UDPSERVER_H__F5949A9E_E088_404B_B76B_772ACFB2ACA8__INCLUDED_)
#define AFX_UDPSERVER_H__F5949A9E_E088_404B_B76B_772ACFB2ACA8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
#include "SDL.h"
#include "SDL_net.h"
#include "UDPPacket.h"
using namespace std;

class CUDPServer  
{
public:
	void listen(Uint32 uiTimeout);
	void sendAll(CUDPPacket poPacket);
   CUDPServer();
   virtual ~CUDPServer();
private:
};

extern CUDPServer go_UDPServer;

#endif // !defined(AFX_UDPSERVER_H__F5949A9E_E088_404B_B76B_772ACFB2ACA8__INCLUDED_)
