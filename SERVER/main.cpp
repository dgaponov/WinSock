// Server WINSock

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <conio.h>
#include <cstdio>
#include <cstdlib>
#include <Windows.h>
#include <winsock2.h>
#include "Thread.h"

using namespace std;

int main() {
    int _port;

    cout << "\tServer WINSock 2.2\n\n";
    cout << "\n\tEnter server port : "; cin >> _port;
    Thread server(_port);
    cout << "\n\tTCP(1) or UDP(2) ?\t" << "Answer (1 / 2) : \n";

    switch(_getch()) {
        case '1' : {
            system("cls");
            try {
                server.all_TCP();
            } catch(string &s) {
                cout << s << endl;
            }
            server.close_server_TCP();
            break;
        }
        case '2' : {
            system("cls");
            try {
                server.all_UDP();
            } catch(string &s) {
                cout << s << endl;
            }
            server.close_server_UDP();
            break;
        }
        default : {
            cout << "Wrong input!\n";
        }
    }

	return 0;
}
