// Client.cpp: implementation of the CClient class.
//
//////////////////////////////////////////////////////////////////////

#include "Client.h"
#include <string.h>


CClient goClientManager;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClient::CClient()
{

}

CClient::~CClient()
{

}

bool CClient::add(IPaddress oIPAddress, char * strName, TCPsocket oSocket)
{
   Client oNewClient;
   long l;

   oNewClient.oIPAddress = oIPAddress;
   strcpy(oNewClient.strClientName , strName);
   oNewClient.oTCPSocket = oSocket;

   for (l = 0 ; l < m_arrClients.size() ; l++ )
   {
	  if (strcmp(m_arrClients[l].strClientName, strName))	  
	  {
		 return false;
	  }
   }
   m_arrClients.push_back(oNewClient);
   return true;
}

char * CClient::getName(long lIndex)
{
   return this->m_arrClients[lIndex].strClientName;
}

bool CClient::get(IPaddress *poIPAddress, char *strName)
{
   long l;

   for (l = 0 ; l < m_arrClients.size() ; l++ )
   {
	  if (strcmp(m_arrClients[l].strClientName, strName))
	  {
		 poIPAddress->host = m_arrClients[l].oIPAddress.host;
		 poIPAddress->host = m_arrClients[l].oIPAddress.host;
		 return true;
	  }
   }
   return false;
}

int CClient::getNumberClients()
{
	return m_arrClients.size();
}

IPaddress * CClient::getIPAddress(int iIndex)
{
	IPaddress *oIP;
	oIP = &m_arrClients[iIndex].oIPAddress;
	return oIP;
}
