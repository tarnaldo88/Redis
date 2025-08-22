#include "ResponseParser.h"

static bool readChar(socket_t sockfd, char &c) {
    ssize_t r = recv(sockfd, &c, 1, 0);
    return (r == 1);
}

//Read a line of text from a socket until it encounters a carriage return
static std::string readLine(socket_t sockfd){
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
    return line;
}

std::string ResponseParser::parseResponse(socket_t sockfd){
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

std::string ResponseParser::parseSimpleString(socket_t sockfd)
{
    return readLine(sockfd);
}

std::string ResponseParser::parseSimpleErrors(socket_t sockfd)
{
    return "(Error) " + readLine(sockfd);
}

std::string ResponseParser::parseSimpleInteger(socket_t sockfd)
{
    return readLine(sockfd);
}

std::string ResponseParser::parseBulkString(socket_t sockfd)
{
    std::string lenStr = readLine(sockfd);
    int length = std::stoi(lenStr);

    if(length == -1) return "(nil)";

    std::string bulk;
    bulk.resize(length);
    int totalRead = 0;

    while(totalRead < length){
        ssize_t r = recv(sockfd, &bulk[totalRead], length - totalRead, 0);

        if(r <= 0) {
            return "(Error) Incomplete bulk data";
        }
        totalRead += r;
    }

    return bulk;
}

std::string ResponseParser::parseArrays(socket_t sockfd)
{
    return std::string();
}
