// TCPServer.cpp: implementation of the CTCPServer class.
//
//////////////////////////////////////////////////////////////////////

#include "TCPServer.h"

CTCPServer go_TCPServer;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTCPServer::CTCPServer()
{
   IPaddress oIP;

   if( SDLNet_ResolveHost( &oIP, NULL, 9999 )==-1 ) 
   {
	  printf( "SDLNet_ResolveHost: %s\n", SDLNet_GetError() );
   }
   else
   {
      m_oSocket = SDLNet_TCP_Open( &oIP );
	  if( !m_oSocket ) 
      {
	     printf( "SDLNet_TCP_Open: %s\n", SDLNet_GetError() );
      }
   }
}

CTCPServer::~CTCPServer()
{

}

CTCPPacket * CTCPServer::listen(Uint32 uiTimeout)
{
   CTCPPacket *poPacket = new CTCPPacket();
   CTCPPacket *poAckPacket = new CTCPPacket();
   CUDPPacket pPlayerInformPacket;
   char strInform[256] = "Player ";
   Uint32 uiStop = SDL_GetTicks() + uiTimeout;
   IPaddress *poNewIP;
   const char  *strHostName;
   int iResult;
   int iData1, iData2;
   long lData1, lData2;
   char strMessage1[256], strMessage2[256];

   TCPsocket oSocket;

   while ( SDL_GetTicks() < uiStop )
   {
	  oSocket = SDLNet_TCP_Accept( m_oSocket );
      if( oSocket ) 
	  {
		 poNewIP = SDLNet_TCP_GetPeerAddress(oSocket);
		 if(!(strHostName = SDLNet_ResolveIP( poNewIP ))) 
		 {
			printf( "SDLNet_ResolveIP: %s\n", SDLNet_GetError() );
		 }
		 else
		 {
			//read packet
			iResult = SDLNet_TCP_Recv(oSocket, poPacket->Data, sizeof(poPacket->Data));
			//Get Type of packet (atm, only login via TCP);
			//Do login check stuff here
			poPacket->getData(&iData1, &iData2, &lData1, &lData2, strMessage1, strMessage2);
			goClientManager.add( poNewIP, strMessage1, oSocket );
			//Send acknowledgement to player
			poAckPacket->setData(iData1, iData2, lData1, lData2, "Now logged in", strMessage2);
			//Inform other players a new player has logged on
			strcat(strInform, strMessage1);
			strcat(strInform, " as joined the game");
			pPlayerInformPacket.setData(strInform);
		    go_UDPServer.sendAll(pPlayerInformPacket);
		 }
	  }
   }   

   return poPacket;
}
