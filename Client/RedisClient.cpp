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
    : host(host), port (port), sockfd(INVALID_SOCK) {}

RedisClient::~RedisClient(){
    disconnect();
}

// RedisClient::

bool RedisClient::connectToServer() {
    // Winsock initialization is handled at application startup (see main.cpp)

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
        
        #ifdef _WIN32
        int rc = connect(sockfd, p->ai_addr, static_cast<int>(p->ai_addrlen));

        if (rc == SOCKET_ERROR) {
            int werr = WSAGetLastError();
            std::cerr << "connect() failed: WSAError=" << werr << "\n";
            CLOSESOCK(sockfd);
            sockfd = INVALID_SOCK;
            continue; // try next addrinfo
        }
        #else
        if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
            std::perror("connect");
            CLOSESOCK(sockfd);
            sockfd = INVALID_SOCK;
            continue; // try next addrinfo
        }
        #endif

        // Success
        break;
    }
    
    freeaddrinfo(res);

    if(sockfd == INVALID_SOCK){
        std::cerr << "Could not connect to: " << host << ":" << port << "\n";
        return false;
    }

    return true;
}

void RedisClient::disconnect(){
    if(sockfd != INVALID_SOCK){
        CLOSESOCK(sockfd);
        sockfd = INVALID_SOCK;
    }
}

socket_t RedisClient::getSocketFd() const {
    return sockfd;
}

bool RedisClient::sendCommand(const std::string &command){
    if(sockfd == INVALID_SOCK){
        return false;
    }

    ssize_t sent = send(sockfd, command.c_str(), command.size(), 0);

    return (sent == (ssize_t)command.size());
}