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

#include "Message.h"
#include "Serialize.h"
#include "Book.h"


class UDPServer {
public:
	UDPServer(std::string address, u_short port);
	~UDPServer();
	void StartComunicate();

public:
	void send(SOCKET &s, char* buf, SOCKADDR* client, int slen, int len = (int)_buflen, int flags = 0);
	void receive(SOCKET &s, char* buf, int len, SOCKADDR* to, int tolen, int flags = 0);

private:
	void InitWS();
	void CreateSocket();
	void BindSocket(u_short port);
	void ConvertIP(std::string &address);
	void Shutdown();
	std::shared_ptr<Book> DBRequestBook(std::string& name);
private:
	static const size_t _buflen = 1024;
	std::string _address;
	u_short _port;
	IN_ADDR ip_to_num;
	WSADATA wsaData;
	WORD DllVersion;
	SOCKADDR_IN client, server;
	SOCKET server_socket;
};