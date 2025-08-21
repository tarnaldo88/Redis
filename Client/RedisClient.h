#ifndef REDIS_CLIENT_H
#define REDIS_CLIENT_H

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "Ws2_32.lib")
    #define CLOSESOCK closesocket
    #include <BaseTsd.h>
    typedef SSIZE_T ssize_t;    
#else
    #include <netdb.h>
    #include <sys/socket.h>
    #include <unistd.h>
    #define CLOSESOCK close
#endif
#include <string>
#include <iostream>
#include <cstring>

// Portable socket type and invalid value
#ifdef _WIN32
using socket_t = SOCKET;
static const socket_t INVALID_SOCK = INVALID_SOCKET;
#else
using socket_t = int;
static const socket_t INVALID_SOCK = -1;
#endif



class RedisClient {
    public:
    RedisClient(const std::string &host, int port);
    ~RedisClient();

    bool connectToServer();
    void disconnect();
    int getSocketFd() const;
    bool sendCommand(const std::string &command);

    private:
    std::string host;
    int port;
    socket_t sockfd;    
};

#endif