#ifndef THREAD_H
#define THREAD_H


class Thread
{
    public:
        Thread(char*, int);
        // for client TCP
        void start_TCP();
        void socket_create_TCP();
        void connect_TCP();
        void send_TCP();
        void close_TCP();
        void all_TCP();
        // for client UDP
        void start_UDP();
        void socket_create_UDP();
        void connect_UDP();
        void send_UDP();
        void close_UDP();
        void all_UDP();
    private:
        WSADATA ws;
        SOCKET Listen;
        SOCKET Connect;
        sockaddr_in Server, Client;
        char Message[1024];
        int ClientLen = sizeof(Client);
        int ServerLen = sizeof(Server);
        int MessageLen;
        int PORT;
        char *IP;
        const int BUFFER = 1024;
        const WORD version = MAKEWORD(2, 2);
};

#endif // THREAD_H
