// UDPServer.cpp: implementation of the CUDPServer class.
//
//////////////////////////////////////////////////////////////////////

#include "UDPServer.h"

CUDPServer go_UDPServer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CUDPServer::CUDPServer()
{

}

CUDPServer::~CUDPServer()
{

}

bool CUDPServer::sendAll(CUDPPacket poPacket)
{
	UDPsocket oSocket;
	int i, iResult;

	m_iCurrentSocket = - 1;
	m_iCurrentChannel = - 1;
	m_iCurrentChannelIP = - 1;


	oSocket=SDLNet_UDP_Open(9998);
	if(!oSocket) 
	{
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}
	m_arrSocket.push_back(oSocket);
	m_iCurrentSocket ++;

	for ( i = 0 ; i < goClientManager.getNumberClients() ; i++ )
	{
		m_iCurrentChannelIP ++;
		if (m_iCurrentChannelIP >= SDLNET_MAX_UDPADDRESSES)
		{
			m_iCurrentChannelIP = 0;
			m_iCurrentChannel ++;
			if (m_iCurrentChannel >= SDLNET_MAX_UDPCHANNELS)
			{
				m_iCurrentChannel = 0;
				m_iCurrentSocket ++;
				oSocket=SDLNet_UDP_Open(9998);
				if(!oSocket) 
				{
					printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
					exit(2);
				}
				m_arrSocket.push_back(oSocket);
			}
		}
		iResult = SDLNet_UDP_Bind( poPacket, iCurrentChannel, goClientManager.getIPAddress[i] );
		if( iResult == -1 ) 
		{
			printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
			// do something because we failed to bind
		}
	}

	for (i = 0 ; i < m_arrSocket.size() ; i++ )
	{
		iResult = SDLNet_UDP_Send( m_arrSocket[i], 0, poPacket );
		if( !iResult ) 
		{
		    printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
		    // do something because we failed to send
		    // this may just be because no addresses are bound to the channel...
		}
	}		
}
