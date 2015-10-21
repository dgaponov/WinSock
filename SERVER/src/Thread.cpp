#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <conio.h>
#include <cstdio>
#include <stdio.h>
#include <Windows.h>
#include <winsock2.h>
#include "Thread.h"

using namespace std;

Thread::Thread(int _port) {
    ZeroMemory(&Server, sizeof(Server));
    ZeroMemory(&Client, sizeof(Client));
    memset(Message, '\0', BUFFER);
    PORT = _port;
}


void Thread::start_server_TCP() {
    if (FAILED(WSAStartup(version, &ws)))
		throw string("Startup server TCP error!");
}

void Thread::socket_create_TCP() {
    if ((Listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == SOCKET_ERROR) {
		WSACleanup();
		throw string("Socket error TCP! " + WSAGetLastError());
	}
}

void Thread::bind_TCP() {
    Server.sin_family = AF_INET;
	Server.sin_port = htons(PORT);
	Server.sin_addr.s_addr = INADDR_ANY;

	if (bind(Listen, (sockaddr*)&Server, sizeof(Server)) == SOCKET_ERROR) {
        closesocket(Listen);
        WSACleanup();
		throw string("Socket bind error TCP! " + WSAGetLastError());
	}
}

void Thread::listen_TCP() {
    if (listen(Listen, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(Listen);
        WSACleanup();
        throw string("Listen error TCP! " + WSAGetLastError());
	}

    cout << "Waiting for connection..." << endl;

	ClientLen = sizeof(Client);
}

void Thread::accept_TCP() {
    if ((Connect = accept(Listen, (sockaddr*)&Client, &ClientLen)) == INVALID_SOCKET) {
		closesocket(Listen);
		WSACleanup();
		throw string("Accept error TCP! " + WSAGetLastError());
	}

	cout << "Succesful connection with " <<
		inet_ntoa(Client.sin_addr) <<
		":" << ntohs(Client.sin_port) << endl;

    closesocket(Listen);
}

void Thread::receive_TCP() {
    memset(Message, '\0', BUFFER);

	if ((MessageLen = recv(Connect, Message, sizeof(Message), 0)) == SOCKET_ERROR) {
		closesocket(Connect);
		WSACleanup();
		throw string("Recieve error TCP! " + WSAGetLastError());
	}

	Message[MessageLen] = '\0';

	cout << "Recieved message: " << Message << endl;
}

void Thread::close_server_TCP() {
    cout << "Connection socket is closed" << endl;

	closesocket(Connect);
	WSACleanup();
}

void Thread::all_TCP() {
    start_server_TCP();
    socket_create_TCP();
    bind_TCP();
    listen_TCP();
    accept_TCP();
    while(1) receive_TCP();
}

void Thread::start_server_UDP() {
    if (FAILED(WSAStartup(version, &ws)))
		throw string("Startup server UDP error!");
}

void Thread::socket_create_UDP() {
    if ((Listen = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == SOCKET_ERROR) {
		WSACleanup();
		throw string("Socket error UDP! " + WSAGetLastError());
	}
}

void Thread::bind_UDP() {
    Server.sin_family = AF_INET;
	Server.sin_port = htons(PORT);
	Server.sin_addr.s_addr = INADDR_ANY;

	if (bind(Listen, (sockaddr*)&Server, sizeof(Server)) == SOCKET_ERROR) {
        closesocket(Listen);
        WSACleanup();
		throw string("Socket bind error TCP! " + WSAGetLastError());
	}
}

void Thread::receive_UDP() {
    memset(Message, '\0', BUFFER);

    ClientLen = sizeof(Client);
	if ((MessageLen = recvfrom(Listen, Message, BUFFER, 0, (sockaddr*)&Client, &ClientLen)) == SOCKET_ERROR) {
		closesocket(Listen);
		WSACleanup();
		throw string("Recieve error UDP! " + WSAGetLastError());
	}

	Message[MessageLen] = '\0';

	cout << "Recieved message from " << inet_ntoa(Client.sin_addr) << ":" <<
                          ntohs(Client.sin_port) << "\n" << Message << endl;
}

void Thread::close_server_UDP() {
    cout << "Listen socket is closed" << endl;

    closesocket(Listen);
    WSACleanup();
}

void Thread::all_UDP() {
    start_server_UDP();
    socket_create_UDP();
    bind_UDP();
    while(1) receive_UDP();
}
