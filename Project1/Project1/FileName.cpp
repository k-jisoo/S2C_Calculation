#include <iostream>
#include <string>

using namespace std;

# define _WINSOCK_DEPRECATED_NO_WARNINGS

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
int main() 
{
	WSAData wsaData;
	int result = WSAStartup(MAKEWORD(2,2), &wsaData);

	if (result != 0)
	{
		cout << "Error" << endl;
		exit(-1);
	}

	SOCKET serverSocket = socket(PF_INET, SOCK_STREAM, 0);
	if (serverSocket == INVALID_SOCKET)
	{
		cout << "Socket Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	SOCKADDR_IN serverSock;
	memset(&serverSock, 0, sizeof(SOCKADDR_IN));
	serverSock.sin_family = AF_INET;
	serverSock.sin_port = htons(7777);
	serverSock.sin_addr.s_addr = INADDR_ANY;

	result = bind(serverSocket, (SOCKADDR*)&serverSock, sizeof(serverSock));
	if (result == SOCKET_ERROR)
	{
		cout << "BIND Error" << endl;
		cout << "BIND Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	result = listen(serverSocket, 0);
	if (result == SOCKET_ERROR)
	{
		cout << "LISTEN Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	cout << "Listen..." << endl;

	SOCKADDR_IN clientSock;
	memset(&clientSock, 0, sizeof(SOCKADDR_IN));
	int clientSockLength = sizeof(clientSock);

	SOCKET clientSocket = accept(serverSocket, (SOCKADDR*)&clientSock, &clientSockLength);
	if (clientSocket == INVALID_SOCKET)
	{
		cout << "Accept Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	string str;
	getline(cin, str);

	int sendByte = send(clientSocket, str.c_str(), (int)strlen(str.c_str()), 0);
	if (sendByte <= 0)
	{
		cout << "Send Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	char buffer[1024] = { 0, };

	int recvByte = recv(clientSocket, buffer, sizeof(buffer), 0);
	if (recvByte <= 0)
	{
		cout << "RecvByte Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}
	
	string res(buffer);

	cout << stoi(res) << endl;

	closesocket(clientSocket);
	
	closesocket(serverSocket);

	WSACleanup();

	return 0;
}