// Client.h: interface for the CClient class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CLIENT_H__4867E43D_55CA_4C88_B525_07AB80F93683__INCLUDED_)
#define AFX_CLIENT_H__4867E43D_55CA_4C88_B525_07AB80F93683__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <vector>
#include "SDL_net.h"
using namespace std;


class CClient  
{
public:
	IPaddress getIPAddress(int iIndex);
	int getNumberClients();
	bool get(IPaddress *poIPAddress, char * strName);
	char * getName(long lIndex);
	bool add(IPaddress oIPAddress, char * strName, TCPsocket oSocket = NULL);
   CClient();
   virtual ~CClient();
private:
   struct Client
   {
      IPaddress oIPAddress;
      char      strClientName[16];
	  TCPsocket oTCPSocket;
   };
   vector <Client> m_arrClients;
};

#endif // !defined(AFX_CLIENT_H__4867E43D_55CA_4C88_B525_07AB80F93683__INCLUDED_)
