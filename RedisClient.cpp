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
    struct addrinfo hints, *res = nullptr;
    std::memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    std::string portStr = std::to_string(port);
    int err = getaddrinfo(host.c_str(), portStr.c_str(), &hints, &res);

    if(err != 0){
        std::cerr << "getaddrinfo: " << gai_strerror(err) << "\n";
        return false;
    }
}