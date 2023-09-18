# define _WINSOCK_DEPRECATED_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>


using namespace std;

#include <WinSock2.h>

#pragma comment(lib, "ws2_32")

int Cal(int num1, int num2, string op);

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
	if (recvByte <= 0)
	{
		cout << "RecvByte Error" << endl;
		cout << "Socket Error Number = " << GetLastError() << endl;
		exit(-1);
	}

	char message[1024] = { 0,  };

	string str(buffer);
	string Cnum1 = str.substr(0, 2);
	string op = str.substr(3, 1);
	string Cnum2 = str.substr(5, 2);
	int num1 = stoi(Cnum1);
	int num2 = stoi(Cnum2);

	int res = Cal(num1, num2, op);

	sprintf(message, "%d", res);

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

int Cal(int num1, int num2, string op) 
{
	int res;

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

	return res;
}