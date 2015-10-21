#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <conio.h>
#include <cstdio>
#include <Windows.h>
#include <winsock2.h>
#include "Thread.h"

using namespace std;

Thread::Thread(char* _ip, int _port) {
    ZeroMemory(&Server, sizeof(Server));
    ZeroMemory(&Client, sizeof(Client));
    memset(Message, '\0', BUFFER);
    PORT = _port;
    IP = _ip;
}

void Thread::start_TCP() {
    if (FAILED(WSAStartup(version, &ws)))
        throw string("Startup error TCP!");
}

void Thread::socket_create_TCP() {
    if ((Connect = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR) {
        WSACleanup();
        throw string("Socket creating error TCP!" + WSAGetLastError());
	}
}

void Thread::connect_TCP() {
    Server.sin_family = AF_INET;
	Server.sin_port = htons(PORT);
	Server.sin_addr.s_addr = inet_addr(IP);

	cout << "Connecting with " << inet_ntoa(Server.sin_addr) << ":" << htons(Server.sin_port) << endl;

	if (connect(Connect, (sockaddr*)&Server, sizeof(Server)) == SOCKET_ERROR) {
        closesocket(Connect);
        WSACleanup();
        throw string("Connect error TCP! " + WSAGetLastError());
	}

	cout << "Connected" << endl;

	getsockname(Connect, (sockaddr*)&Client, &ClientLen);

    cout << inet_ntoa(Client.sin_addr) << ":" << htons(Client.sin_port) << endl;
}

void Thread::send_TCP() {
    memset(Message, '\0', BUFFER);
    cout << "Write message: ";
    fflush(stdin);
    gets(Message);

    MessageLen = sizeof(Message);

    if(send(Connect, Message, MessageLen, 0) == SOCKET_ERROR) {
        closesocket(Connect);
        WSACleanup();
        throw string("Send error TCP! " + WSAGetLastError());
    }

    cout << "Successful sending" << endl;
}

void Thread::close_TCP() {
    cout << "Closing connection with server TCP" << endl;
    closesocket(Connect);
    WSACleanup();
}

void Thread::all_TCP() {
    start_TCP();
    socket_create_TCP();
    connect_TCP();
    while(1) send_TCP();
}

void Thread::start_UDP() {
    if (FAILED(WSAStartup(version, &ws)))
		throw string("Startup error UDP!");
}

void Thread::socket_create_UDP() {
    if ((Connect = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
		WSACleanup();
		throw string("Socket create error UDP! " + WSAGetLastError());
	}
}

void Thread::connect_UDP() {
    Server.sin_family = AF_INET;
	Server.sin_port = htons(PORT);
	Server.sin_addr.s_addr = inet_addr(IP);
}

void Thread::send_UDP() {
    memset(Message, '\0', BUFFER);
    cout << "Write message: ";
    fflush(stdin);
    gets(Message);

    MessageLen = strlen(Message);

    if(sendto(Connect, Message, MessageLen, 0, (sockaddr*)&Server, ServerLen) == SOCKET_ERROR) {
        closesocket(Connect);
        WSACleanup();
        throw string("Send error UDP! " + WSAGetLastError());
    }

    cout << "Successful sending" << endl;
}

void Thread::close_UDP() {
    cout << "Closing connection with server UDP" << endl;
    closesocket(Connect);
    WSACleanup();
}

void Thread::all_UDP() {
    start_UDP();
    socket_create_UDP();
    connect_UDP();
    while(1) send_UDP();
}
