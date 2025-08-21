#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include <string>
#include <regex>

class CommandHandler {
    public:
        //split commands into tokens
        static std::vector<std::string> splitArgs(const std::string &input);
        
        //Get RESP commands from the vector args
        static std::string buildRESPCommand(const std::vector<std::string> &args);

    private:

};


#endif // COMMAND_HANDLER_H