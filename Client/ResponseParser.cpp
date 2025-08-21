#include "ResponseParser.h"

static bool readChar(int sockfd, char &c) {
    ssize_t r = recv(sockfd, &c, 1, 0);
    return (r == 1);
}

//Read a line of text from a socket until it encounters a carriage return
static std::string readLine(int sockfd){
    std::string line;
    char c;
    while(readChar(sockfd, c)){
        if(c == '\r'){
            //expect \n next; read and break
            readChar(sockfd, c);
            break;
        }
        line.push_back(c);
    }
}

std::string ResponseParser::parseResponse(int sockfd){
    char prefix;
    if(!readChar(sockfd, prefix)) {
        return ("(Error) No response or connection closed.");
    }

    switch(prefix){
        case '+' : return ResponseParser::parseSimpleString(sockfd);
        case '-' : return ResponseParser::parseSimpleErrors(sockfd);
        case ':' : return ResponseParser::parseSimpleInteger(sockfd);
        case '$' : return ResponseParser::parseBulkString(sockfd);
        case '*' : return ResponseParser::parseArrays(sockfd);
        default:
            return "(Error) Unknown reply type.";
    }
}

std::string ResponseParser::parseSimpleString(int sockfd)
{
    return readLine(sockfd);
}

std::string ResponseParser::parseSimpleErrors(int sockfd)
{
    return std::string();
}

std::string ResponseParser::parseSimpleInteger(int sockfd)
{
    return std::string();
}

std::string ResponseParser::parseBulkString(int sockfd)
{
    return std::string();
}

std::string ResponseParser::parseArrays(int sockfd)
{
    return std::string();
}
