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

    private:
    RedisClient redisClient;
};


#endif