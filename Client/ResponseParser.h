#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

#include <string>
#include <iostream>
#include <sstream>
#include "RedisClient.h"
#include <cstdlib>


class ResponseParser{
public:
    //Function that reads from given socket and return parsed response string
    static std::string parseResponse(socket_t sockfd);   

private:
    //Redis Serialization Protocol 2
    static std::string parseSimpleString(socket_t sockfd);
    static std::string parseSimpleErrors(socket_t sockfd);
    static std::string parseSimpleInteger(socket_t sockfd);
    static std::string parseBulkString(socket_t sockfd);
    static std::string parseArrays(socket_t sockfd);
};

#endif