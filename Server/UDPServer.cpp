#include "UDPServer.h"

UDPServer::UDPServer(PCSTR address, u_short port) : _address(address), _port(port)
{
	InitWS();
	CreateSocket();
	ConvertIP(address);
	BindSocket(port);
}

UDPServer::~UDPServer()
{
	Shutdown();
}

void UDPServer::StartComunicate()
{
	char client_message[1024];
	int slen = sizeof(SOCKADDR_IN);
	
	while (true) 
	{
		if (recvfrom(server_socket, (char*)&client_message, _buflen, 0, (SOCKADDR*)&client, &slen) == SOCKET_ERROR)
		{
			std::cout << "recvfrom() failed with error code: " << WSAGetLastError() << '\n';
			Shutdown();
			exit(1);
		}
		
		// Get book from database
		std::string clean_string = std::string(client_message);
		auto db_res = DBRequestBook(clean_string);
		
		// Database data to JSON string
		std::string server_response_json;
		CJsonSerializer::Serialize(db_res.get(), server_response_json);
		
		// Send book responese or default object { name: "Not found"... } 
		if (sendto(server_socket, server_response_json.c_str(), (int)strlen(server_response_json.c_str()), 0, (SOCKADDR*)&client, slen) == SOCKET_ERROR)
		{
			std::cout << "sendto() failed with error code: " << WSAGetLastError();
			Shutdown();
			exit(1);
		}

		clean_string.clear();
		memset(client_message, 0, sizeof(client_message));
	}
}

void UDPServer::Shutdown()
{
	if (server_socket >= 0) closesocket(server_socket);
	WSACleanup();
}

std::shared_ptr<Book> UDPServer::DBRequestBook(std::string &name)
{
	try {
		std::string connectionString = "host=localhost port=5432 dbname=books_shop user=postgres password=2203";
		
		pqxx::connection connectionObject(connectionString.c_str());

		pqxx::work worker(connectionObject);

		auto default_response = std::make_shared<Book>();

		if (name.empty()) 
		{
			return default_response;
		}

		std::string requestString = "SELECT * FROM book_list WHERE LOWER(name) = LOWER('" + name + "')";
		pqxx::result response = worker.exec(requestString);
	
		if (!response.empty())
		{
			auto new_book = std::make_shared<Book>(
				std::string(response[0][1].c_str()),
				std::string(response[0][5].c_str()),
				response[0][3].as<int>(),
				response[0][4].as<int>()
			);

			return new_book;
		}
		else 
		{
			return default_response;
		}
	}
	catch (std::exception const& e) {
		std::cerr << "ERROR: " << e.what() << '\n';
	}
}

void UDPServer::InitWS()
{
	int result;

	DllVersion = MAKEWORD(2, 2);

	result = WSAStartup(DllVersion, &wsaData);

	if (result != 0) 
	{
		std::cout << "Error WinSock version initialzation: " << WSAGetLastError() << '\n';
		exit(1);
	}
	else 
	{
		std::cout << "WinSock initialization is OK" << '\n';
	}
}

void UDPServer::CreateSocket()
{
	server_socket = socket(AF_INET, SOCK_DGRAM, 0);
	if (server_socket == INVALID_SOCKET) 
	{
		std::cout << "Error initialization socket: "
			<< WSAGetLastError() << '\n';
		Shutdown();
		exit(1);
	}
	else
	{
		std::cout << "Server socket initialization is OK" << '\n';
	}
}

void UDPServer::BindSocket(u_short port)
{
	int result;
	ZeroMemory(&server, sizeof(server));
	ZeroMemory(&client, sizeof(client));

	server.sin_family = AF_INET;
	server.sin_addr = ip_to_num;
	server.sin_port = htons(port);
	
	result = bind(server_socket, (SOCKADDR*)&server, sizeof(server));
	if (result != 0)
	{
		std::cout << "Error socket binding to server info. Error: "
			<< WSAGetLastError() << '\n';
		Shutdown();
		exit(1);
	}
	else 
	{
		std::cout << "Binding socket to server info is OK" << '\n';
	}
}

void UDPServer::send(SOCKET &s, char* buf, SOCKADDR* client, int slen, int len, int flags)
{
	if (recvfrom(s, (char*) &buf, len, flags, (SOCKADDR*)&client, &slen) == SOCKET_ERROR)
	{
		std::cout << "recvfrom() failed with error code: " << WSAGetLastError() << '\n';
		Shutdown();
		exit(1);
	}
}

void UDPServer::receive(SOCKET &s, char* buf, int len, SOCKADDR* to, int tolen, int flags)
{
	if (sendto(s, buf, len, flags, to, tolen) == SOCKET_ERROR)
	{
		std::cout << "sendto() failed with error code: " << WSAGetLastError();
		Shutdown();
		exit(1);
	}
}

void UDPServer::ConvertIP(PCSTR &address)
{
	int result;
	result = inet_pton(AF_INET, address, &ip_to_num);
	if (result <= 0) {
		std::cout << "Error in IP translation to special numeric format" << '\n';
		exit(1);
	}
}

