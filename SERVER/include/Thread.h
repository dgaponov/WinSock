#ifndef THREAD_H
#define THREAD_H


class Thread
{
    public:
        Thread(int);
        // for server TCP
        void start_server_TCP();
        void socket_create_TCP();
        void bind_TCP();
        void listen_TCP();
        void accept_TCP();
        void receive_TCP();
        void close_server_TCP();
        void all_TCP();

        // for server UDP
        void start_server_UDP();
        void socket_create_UDP();
        void bind_UDP();
        void receive_UDP();
        void close_server_UDP();
        void all_UDP();
    private:
        WSADATA ws;
        SOCKET Listen;
        SOCKET Connect;
        sockaddr_in Server, Client;
        char Message[1024];
        int ClientLen;
        int MessageLen;
        int PORT;
        const int BUFFER = 1024;
        const WORD version = MAKEWORD(2, 2);
};

#endif // THREAD_H
