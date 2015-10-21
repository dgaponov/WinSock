// Client WINSock

#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <string>
#include <thread>
#include <conio.h>
#include <cstdlib>
#include <Windows.h>
#include <winsock2.h>
#include "Thread.h"

using namespace std;

int main() {
    int _port;
    char _ip[17];

    cout << "\tClient WINSock 2.2\n\n";
    cout << "\tEnter server IP : "; cin >> _ip;
    cout << "\n\tEnter server port : "; cin >> _port;
    Thread client(_ip, _port);
    cout << "\n\tTCP(1) or UDP(2) ?\t" << "Answer (1 / 2) : \n";

    switch(_getch()) {
        case '1' : {
            system("cls");
            try {
                client.all_TCP();
            } catch(string &s) {
                cout << s << endl;
            }
            client.close_TCP();
            break;
        }
        case '2' : {
            system("cls");
            try {
                client.all_UDP();
            } catch(string &s) {
                cout << s << endl;
            }
            client.close_UDP();
            break;
        }
        default : {
            cout << "\tWrong input!\n";
        }
    }

    return 0;
}
