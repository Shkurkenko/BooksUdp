#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS

#include "UDPServer.h"

#define BUFLEN_DEFAULT 1024
#define PORT_DEFAULT 8888
#define IP_DEFAULT "127.0.0.1"

int main(int argc, char* argv[])
{
	system("title UDP Server");
	setlocale(LC_ALL, "en_US.UTF-8");
	
	UDPServer udpServer = UDPServer(IP_DEFAULT, PORT_DEFAULT);
	udpServer.StartComunicate();

	return 0;
}

