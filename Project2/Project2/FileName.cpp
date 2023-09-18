# define _WINSOCK_DEPRECATED_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>


using namespace std;

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")
int main()
{
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET serverSocket = socket(PF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN serverSock;
	ZeroMemory(&serverSock, 0);
	serverSock.sin_family = AF_INET;
	serverSock.sin_addr.s_addr = inet_addr("172.16.2.162");
	serverSock.sin_port = htons(7777);

	int result = connect(serverSocket, (SOCKADDR*)&serverSock, sizeof(serverSock));
	if (result == SOCKET_ERROR)
	{
		cout << "Socket Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	char buffer[1024] = { 0, };

	int recvByte = recv(serverSocket, buffer, sizeof(buffer), 0);
	string str(buffer);
	string Cnum1 = str.substr(0, 2);
	string op = str.substr(3, 1);
	string Cnum2 = str.substr(5, 2);
	double num1 = stoi(Cnum1);
	double num2 = stoi(Cnum2);
	int res = 0;

	if (op == "+")
		res = num1 + num2;
	else if (op == "-")
		res = num1 - num2;
	else if (op == "*")
		res = num1 * num2;
	else if (op == "/")
		res = num1 / num2;
	else
		res = 0;


	if (recvByte <= 0)
	{
		cout << "RecvByte Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	cout << "Recv : " << buffer << endl;

	char message[1024] = { res };

	int sendByte = send(serverSocket, message, (int)strlen(message), 0);
	if (sendByte <= 0)
	{
		cout << "Send Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	cout << "client send : " << buffer << endl;

	closesocket(serverSocket);

	WSACleanup();

	return 0;
}