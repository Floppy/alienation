#ifdef WIN32
#include <windows.h>
#include <conio.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
#include "SDL.h"
#include "SDL_thread.h"
#include "SDL_net.h"
#include "UDPServer.h"
#include "TCPServer.h"

SQLHENV			 g_hEnv;				// Handle ODBC environment
long				 g_lResult;			// result of functions
SQLHDBC			 g_hDbc;				// Handle connection
unsigned char	 g_strStatus[10];	// Status SQL
bool				 g_bEnd = false;

int doTCP(void *unused)
{
	while (!g_bEnd)
	{
		go_TCPServer.listen(250);
	}
	return 1;
}

int doUDP(void *unused)
{
	while (!g_bEnd)
	{
		go_UDPServer.listen(250);
	}
	return 1;
}

int main(int argc, char **argv)
{
	SDL_Thread *TCPThread, *UDPThread;

												//////////////////////////////////////////////
												//Setup ODBC stuff first                    //
												//////////////////////////////////////////////

												//////////////////////////////////////////////
												//Allocate Environment handle and register  //
												//version                                   //
												//////////////////////////////////////////////

	g_lResult=SQLAllocHandle(SQL_HANDLE_ENV,SQL_NULL_HANDLE,&g_hEnv);
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error AllocHandle\n");
		exit(0);
	}


	g_lResult=SQLSetEnvAttr(g_hEnv, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, 0); 
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error SetEnv\n");
		SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
		exit(0);
	}
												//////////////////////////////////////////////
												//Allocate connection handle, set timeout   //
												//////////////////////////////////////////////

	g_lResult = SQLAllocHandle(SQL_HANDLE_DBC, g_hEnv, &g_hDbc); 
	if ((g_lResult != SQL_SUCCESS) && (g_lResult != SQL_SUCCESS_WITH_INFO))
	{
		printf("Error AllocHDB %d\n",g_lResult);
		SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
		exit(0);
	}
	SQLSetConnectAttr(g_hDbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER *)5, 0);


												//////////////////////////////////////////////
												//Initialise SDL and SDL_net                //
												//////////////////////////////////////////////

	if(SDL_Init(0)==-1) 
	{
		printf("SDL_Init: %s\n", SDL_GetError());
	}

	if(SDLNet_Init()==-1) 
	{
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}

												//////////////////////////////////////////////
												//Create the TCP listining socket           //
												//////////////////////////////////////////////

	go_TCPServer.createSocket();

												//////////////////////////////////////////////
												//Create threads for running the tcp and    //
												//udp listeners                             //
												//////////////////////////////////////////////

	TCPThread = SDL_CreateThread(doTCP, NULL);
	if ( TCPThread == NULL ) 
	{
		fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
	}
	printf("Started TCP Listener\n");

	UDPThread = SDL_CreateThread(doUDP, NULL);
	if ( UDPThread == NULL ) 
	{
		fprintf(stderr, "Unable to create thread: %s\n", SDL_GetError());
	}
	printf("Started UDP Listener\n");

												//////////////////////////////////////////////
												//Watch keyboard input for q being pressed  //
												//////////////////////////////////////////////

	char inp = getch();
	while (inp != 'q' && inp != 'Q')
	{
		inp = getch();
	}

												//////////////////////////////////////////////
												//Quit the threads                          //
												//////////////////////////////////////////////

	g_bEnd = true;
	SDL_WaitThread(TCPThread, NULL);
	SDL_WaitThread(UDPThread, NULL);

												//////////////////////////////////////////////
												//Clean up                                  //
												//////////////////////////////////////////////


	SQLFreeHandle(SQL_HANDLE_DBC,g_hDbc);
	SQLFreeHandle(SQL_HANDLE_ENV, g_hEnv);
	
	SDL_Quit();
	SDLNet_Quit();
	return 1;
}
