#ifndef CLI_H
#define CLI_H
#include "RedisClient.h"
#include "ResponseParser.h"

#include <string>
#include <vector>
#include "CommandHandler.h"
#include <sstream>
//...

class CLI {
    public:
        CLI(const std::string &host, int port);
        void run();
        void executeCommands(const std::vector<std::string> &commandArgs);

    private:
    std::string host;
    int port;
    RedisClient redisClient;
    
};


#endif