#include "ResponseParser.h"

static bool readChar(int sockfd, char &c) {
    ssize_t r = recv(sockfd, &c, 1, 0);
    return (r == 1);
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
            return "";
    }

}

    
    
    
    