// UDPServer.cpp: implementation of the CUDPServer class.
//
//////////////////////////////////////////////////////////////////////

#include "UDPServer.h"

enum eMsgType {
	MSG_NOMESSAGE     = 0,
	MSG_TEXTMESSAGE   = 1,
	MSG_LOGINREQUEST  = 2,  // client's first message to server
	MSG_LOGINREPLY    = 3,  // server's response
	MSG_CONNECTNOTICE = 4,  // player's connect status has changed
	MSG_SNAPSHOT      = 5,
	MSG_MOVENOTICE    = 6,  // player has moved
	MSG_SPAWNNOTICE   = 7,
	MSG_DEATHNOTICE   = 8,
	MSG_COLLIDENOTICE = 9,
	MSG_KEEPALIVE     = 10
};

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

void CUDPServer::sendAll(CUDPPacket poPacket)
{
	UDPsocket oSocket;
	int i, iResult;
	IPaddress *poIPAddress;


	oSocket=SDLNet_UDP_Open(0);
	if(!oSocket) 
	{
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
		exit(2);
	}	
	
	for ( i = 0 ; i < goClientManager.getNumberClients() ; i++ )
	{
		poIPAddress = goClientManager.getIPAddress(i);


		iResult = SDLNet_UDP_Bind( oSocket, -1, poIPAddress );
		if( iResult == -1 ) 
		{
			printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
			// do something because we failed to bind
		}
		poPacket.send(oSocket, MSG_TEXTMESSAGE);
		SDLNet_UDP_Unbind( oSocket, iResult );
	}	
	SDLNet_UDP_Close( oSocket );

}

void CUDPServer::listen(Uint32 uiTimeout)
{
	Uint32 uiStop = SDL_GetTicks() + uiTimeout;
	CUDPPacket oPacket;
	UDPsocket oSocket;

	oPacket.setLastMessageRecievedType(MSG_NOMESSAGE);

	oSocket = SDLNet_UDP_Open(9998);
	if ( !oSocket ) 
	{
		printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
	}


	while (SDL_GetTicks() < uiStop)
	{
		oPacket.recieve(oSocket);
		if ( oPacket.getLastMessageRecievedType() != MSG_NOMESSAGE )
		{
			//send message to other clients
			go_UDPServer.sendAll(oPacket);
		}
	}
	SDLNet_UDP_Close( oSocket );

}
