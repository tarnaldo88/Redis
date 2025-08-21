#include "CommandHandler.h"

std::vector<std::string> CommandHandler::splitArgs(const std::string &input) {
    std::vector<std::string> tokens;

    //Match words or quoted strings using Regex
    std::regex rgx(R"((\"[^\"]+\"|\S+))");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), rgx);
   auto words_end =  std::sregex_iterator();

    return tokens;
}