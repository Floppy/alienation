#include "SDL.h"
#include "SDL_net.h"
#include "UDPServer.h"
#include "TCPServer.h"

int main()
{
	go_TCPServer = CTCPServer();
	go_UDPServer = CUDPServer();
	return 1;
}