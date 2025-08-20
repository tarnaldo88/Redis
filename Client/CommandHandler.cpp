#include "CommandHandler.h"

std::vector<std::string> CommandHandler::splitArgs(const std::string &input) {
    std::vector<std::string> tokens;

    //Match words or quoted strings using Regex
    std::regex rgx(R"((\"[^\"]))");

    return tokens;
}