#include "UDPPacket.h"


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



CUDPPacket::CUDPPacket()
{
	m_poMessage = new sMessage;
}

CUDPPacket::~CUDPPacket()
{
	delete m_poMessage;
}

char * CUDPPacket::getData()
{
	return " ";
}

void CUDPPacket::setData(char *poData)
{

}

void CUDPPacket::setData(char *strUser, char *strMessage)
{
	m_poMessage->iId = 1;
	strcpy(m_poMessage->strUser, strUser);
	strcpy(m_poMessage->strMessage, strMessage);
}

void CUDPPacket::send(UDPsocket poSocket, int iMessageType)
{
	int iResult;
	UDPpacket *oPacket;


	switch(iMessageType)
	{
		case MSG_TEXTMESSAGE:
			oPacket = SDLNet_AllocPacket( sizeof( sMessage ) );
			oPacket->data = (Uint8 *)m_poMessage;
			iResult = SDLNet_UDP_Send( poSocket, 0, oPacket );
			if( !iResult ) 
			{
				 printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
			}
			SDLNet_FreePacket( oPacket );
			break;
	}
}

int CUDPPacket::recieve(UDPsocket oSocket)
{
	UDPpacket *oPacket;
	int iNumRecieved;
	int iMsgType;
	int iChannel, i;

	
	oPacket = SDLNet_AllocPacket( 1024 );

	for ( i = 0 ; i < goClientManager.getNumberClients() ; i++ )
	{
		iChannel = SDLNet_UDP_Bind(oSocket, -1, goClientManager.getIPAddress(i) );
		if ( iChannel == -1 )
		{
			printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
		}

		iNumRecieved = SDLNet_UDP_Recv(oSocket, oPacket);
		if ( iNumRecieved )
		{
			iMsgType = (int)oPacket->data[0];		
			switch (iMsgType)
			{
			case MSG_TEXTMESSAGE:
				m_poMessage = (sMessage *)oPacket->data;
				break;
			}
			m_iLastMessageRecievedType = iMsgType;
			return iMsgType;
		}
		SDLNet_UDP_Unbind( oSocket, iChannel );
	}
	SDLNet_FreePacket( oPacket );
	return MSG_NOMESSAGE;
}

void CUDPPacket::setLastMessageRecievedType(int iLastMessage)
{
	m_iLastMessageRecievedType = iLastMessage;
}

int CUDPPacket::getLastMessageRecievedType()
{
	return m_iLastMessageRecievedType;
}
