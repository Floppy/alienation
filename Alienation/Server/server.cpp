#include "SDL.h"
#include "SDL_net.h"
#include "UDPServer.h"
#include "TCPServer.h"

int main(int argc, char **argv)
{

	if(SDL_Init(0)==-1) 
	{
		printf("SDL_Init: %s\n", SDL_GetError());
	}

	if(SDLNet_Init()==-1) 
	{
		printf("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}

	go_TCPServer.createSocket();

	while (1)
	{
		go_TCPServer.listen(250);
		go_UDPServer.listen(250);
		SDL_Delay(500);
	}
	return 1;
}