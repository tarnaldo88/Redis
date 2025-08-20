#ifndef COMMAND_HANDLER_H
#define COMMAND_HANDLER_H

#include <vector>
#include <string>
#include <regex>

class CommandHandler {
    public:

        static std::vector<std::string> splitArgs(const std::string &input);


    private:

};


#endif // COMMAND_HANDLER_H