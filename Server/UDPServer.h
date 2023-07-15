#pragma once

#define _SILENCE_ALL_CXX20_DEPRECATION_WARNINGS

#pragma comment (lib, "ws2_32.lib")

#include <iostream>
#include <algorithm>
#include <string>
#include <exception>
#include <optional>
#include <memory>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>

#include <pqxx/pqxx>

#include "Serialize.h"
#include "Book.h"


class UDPServer {
public:
	UDPServer(PCSTR address, u_short port);
	~UDPServer();
	void StartComunicate();

private:
	void InitWS();
	void CreateSocket();
	void BindSocket(u_short port);
	void ConvertIP(PCSTR &address);
	void Shutdown();
	std::shared_ptr<Book> DBRequestBook(std::string& name);
private:
	static const size_t _buflen = 1024;
	PCSTR _address;
	u_short _port;
	IN_ADDR ip_to_num;
	WSADATA wsaData;
	WORD DllVersion;
	SOCKADDR_IN client, server;
	SOCKET server_socket;
};
