#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS

#include "Config.h"
#include "UDPServer.h"

int main(int argc, char* argv[])
{
	system("title UDP Server");
	setlocale(LC_ALL, "en_US.UTF-8");
	
	UDPServer udpServer = UDPServer(CONFIG::IP_DEFAULT, CONFIG::PORT_DEFAULT);
	udpServer.StartComunicate();

	return 0;
}

