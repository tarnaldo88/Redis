#ifndef REDIS_CLIENT_H
#define REDIS_CLIENT_H

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
    #define CLOSESOCK closesocket
#else
    #include <netdb.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #define CLOSESOCK close
#endif
#include <string>
#include <iostream>
#include <cstring>



class RedisClient {
    public:
    RedisClient(const std::string &host, int port);
    ~RedisClient();

    bool connectToServer();
    void disconnect();


    private:
    std::string host;
    int port;
    int sockfd;    
};

#endif