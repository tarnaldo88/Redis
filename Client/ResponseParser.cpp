#include "ResponseParser.h"

static bool readChar(int sockfd, char &c) {
    ssize_t r = recv(sockfd, &c, 1, 0);
}

std::string parseResponse(int sockfd){
    char prefix;

}