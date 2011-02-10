// TCPPacket.cpp: implementation of the CTCPPacket class.
//
//////////////////////////////////////////////////////////////////////

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


#include "TCPPacket.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTCPPacket::CTCPPacket()
{
	m_poLoginReply = new sLoginReply;
	m_poLoginMessage = new sLoginMessage;
}

CTCPPacket::~CTCPPacket()
{
	delete m_poLoginReply;
	delete m_poLoginMessage;
}


bool CTCPPacket::send(TCPsocket poSocket, int iMsgType)
{
	int iLen, iResult;
	Uint8 *uiBuffer;

	switch (iMsgType)
	{
	case MSG_LOGINREPLY:
		iLen = sizeof(sLoginReply);
		uiBuffer = (Uint8 *)m_poLoginReply;

		iResult=SDLNet_TCP_Send(poSocket, uiBuffer, iLen);
		if( iResult < iLen ) 
		{
			 printf("SDLNet_TCP_Send: %s\n", SDLNet_GetError());
			return false;
		}
	}
	return true;
}

int CTCPPacket::recieve(TCPsocket poSocket)
{
	int iMaxLen = 1024;
	Uint8 uiBuffer[1024];
	int iResult;
	int iMsgType;

	iResult=SDLNet_TCP_Recv(poSocket,uiBuffer,iMaxLen);
	if(iResult<=0) 
	{
		return MSG_NOMESSAGE;
	}

	iMsgType = (int)uiBuffer[0];

	switch (iMsgType)
	{
	case MSG_LOGINREQUEST:
		m_poLoginMessage = (sLoginMessage *)uiBuffer;
		break;
	}

	return iMsgType;

}

void CTCPPacket::getLoginRequest(char *strUserName, char *strPassword)
{
	strcpy(strUserName, m_poLoginMessage->strUserName);
	strcpy(strPassword, m_poLoginMessage->strPassword);
}

void CTCPPacket::setLoginAcknowledgement(char *strUserName, char *strMessage)
{
	m_poLoginReply->iId = MSG_LOGINREPLY;
	strcpy(m_poLoginReply->strMessage, strMessage);
	strcpy(m_poLoginReply->strUserName, strUserName);
}
