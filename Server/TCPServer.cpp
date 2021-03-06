// TCPServer.cpp: implementation of the CTCPServer class.
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


#include "TCPServer.h"
#include "Client.h"
#include "UDPServer.h"

CTCPServer go_TCPServer;
extern SQLHENV			 g_hEnv;				// Handle ODBC environment
extern long				 g_lResult;			// result of functions
extern SQLHDBC			 g_hDbc;				// Handle connection
extern unsigned char	 g_strStatus[10];	// Status SQL

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTCPServer::CTCPServer()
{

}

CTCPServer::~CTCPServer()
{

}

CTCPPacket * CTCPServer::listen(Uint32 uiTimeout)
{
	CPilot *poPilot;
	CTCPPacket *poPacket = new CTCPPacket();
	CTCPPacket *poAckPacket = new CTCPPacket();
	CUDPPacket pPlayerInformPacket;
	char strInform[256] = "Player ";
	Uint32 uiStop = SDL_GetTicks() + uiTimeout;
	IPaddress *poNewIP;
	const char  *strHostName;
	int iResult;
	char strUserName[16], strPassword[16];

	TCPsocket oSocket;
	poPilot = new CPilot();

	while ( SDL_GetTicks() < uiStop )
	{
		//Accept new connections
		oSocket = SDLNet_TCP_Accept( m_oSocket );
		if( oSocket ) 
		{
			printf ("Socket accepted packet \n");
			poNewIP = SDLNet_TCP_GetPeerAddress(oSocket);
			if(!(strHostName = SDLNet_ResolveIP( poNewIP ))) 
			{
				printf( "SDLNet_ResolveIP: %s\n", SDLNet_GetError() );
			}
			else
			{
																	//////////////////////////////////////////////
																	//read packet. get type of packet (atm,     //
																	//only login via TCP);                      //
																	//////////////////////////////////////////////

				iResult = poPacket->recieve(oSocket);
				switch (iResult)
				{
				case MSG_LOGINREQUEST:
																	//////////////////////////////////////////////
																	//Get sent username and password and check  //
																	//them against the database                 //
																	//////////////////////////////////////////////

					poPacket->getLoginRequest(strUserName, strPassword);
					if (poPilot->findByPilotName(strUserName))
					{

																	//////////////////////////////////////////////
																	//Pilot found in database, now check for    //
																	//correct password                          //
																	//////////////////////////////////////////////

						if ((strcmp(strPassword, poPilot->getPassword())) != -1)
						{
																	//////////////////////////////////////////////
																	//Username and password were valid, no      //
																	//errors occured                            //
																	//////////////////////////////////////////////

							goClientManager.add( *poNewIP, strUserName, oSocket );
																	//////////////////////////////////////////////
																	//Send acknowledgement to player            //
																	//////////////////////////////////////////////

							poAckPacket->setLoginAcknowledgement(strUserName, "Welcome to the server!");
							poAckPacket->send(oSocket, MSG_LOGINREPLY);
																	//////////////////////////////////////////////
																	//Inform other players a new player has     //
																	//logged on                                 //
																	//////////////////////////////////////////////

							strcat(strInform, strUserName);
							strcat(strInform, " has joined the game");
							pPlayerInformPacket.setData(strUserName, strInform);
							go_UDPServer.sendAll(pPlayerInformPacket);
						}
					}
					break;
				default:
					break;
				}
			}
		}
	}   

	return poPacket;
}

bool CTCPServer::createSocket()
{
   IPaddress oIP;

   if( SDLNet_ResolveHost( &oIP, NULL, 9999 )==-1 ) 
   {
	  printf( "SDLNet_ResolveHost: %s\n", SDLNet_GetError() );
	  return false;
   }
   else
   {
		m_oSocket = SDLNet_TCP_Open( &oIP );
		if( !m_oSocket ) 
      {
	     printf( "SDLNet_TCP_Open: %s\n", SDLNet_GetError() );
		  return false;
      }
		return true;
   }

}


