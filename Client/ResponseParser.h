#ifndef RESPONSEPARSER_H
#define RESPONSEPARSER_H

#include <string>
#include <iostream>
#include <sstream>

#ifdef _WIN32
    #include <windows.h>
    #include <BaseTsd.h>
    #include <winsock2.h>
    #include <ws2tcpip.h>
    typedef SSIZE_T ssize_t;
#else
    #include <unistd.h>
    #include <sys/types.h>
    #include <sys/socket.h> 
    #include <sys/types.h>
#endif

#include <cstdlib>


class ResponseParser{
public:
    //Function that reads from given socket and return parsed response string
    static std::string parseResponse(int sockfd);   

private:
    //Redis Serialization Protocol 2
    static std::string parseSimpleString(int sockfd);
    static std::string parseSimpleErrors(int sockfd);
    static std::string parseSimpleInteger(int sockfd);
    static std::string parseBulkString(int sockfd);
    static std::string parseArrays(int sockfd);
};

#endif