#include "RedisClient.h"


RedisClient::RedisClient(const std::string &host, int port) 
    : host(host), port (port), sockfd(-1) {}