/*
Establish TCP Connection to Redis (RedisCLient)
    Berkeley sockets to open TCP connection
    IPv4 and IPv6 'getaddrinfo
    Implements:
    connectToServer() -> Establish the connection
    sendCommand() -> Sends a command over the socket.
    disconnect() -> closes the socket when finished
*/


#include "RedisClient.h"


RedisClient::RedisClient(const std::string &host, int port) 
    : host(host), port (port), sockfd(-1) {}

RedisClient::~RedisClient(){
    disconnect();
}

// RedisClient::

bool RedisClient::connectToServer() {
    #ifdef _WIN32
    WSADATA wsaData;
    int err = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if(err != 0){
        std::cerr << "WSAStartup failed: " << err << "\n";
        return false;
    }    
    #endif
    struct addrinfo hints, *res = nullptr;

    //clearing the hints struct
    std::memset(&hints, 0, sizeof(hints));

    //Ipv4 IPv6
    hints.ai_family = AF_UNSPEC; 

    //TCP
    hints.ai_socktype = SOCK_STREAM;

    std::string portStr = std::to_string(port);
    int err = getaddrinfo(host.c_str(), portStr.c_str(), &hints, &res);

    if(err != 0){
        std::cerr << "getaddrinfo: " << gai_strerror(err) << "\n";
        return false;
    }

    for (auto p = res; p != nullptr; p = p->ai_next){
        sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol);

        if(sockfd == INVALID_SOCK)
            continue;

        if(connect(sockfd, p->ai_addr, p->ai_addrlen) == 0){
            break;
        }

        CLOSESOCK(sockfd);
        sockfd = INVALID_SOCK;
    }
    freeaddrinfo(res);

    if(sockfd == INVALID_SOCK){
        std::cerr << "Could not connect to: " << host << ":" << port << "\n";
        return false;
    }

    #ifdef _WIN32
    WSACleanup();
    #endif

    return true;
}

void RedisClient::disconnect(){
    if(sockfd != INVALID_SOCK){
        CLOSESOCK(sockfd);
        sockfd = INVALID_SOCK;
    }
}