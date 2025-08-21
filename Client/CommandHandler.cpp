#include "CommandHandler.h"

std::vector<std::string> CommandHandler::splitArgs(const std::string &input) {
    std::vector<std::string> tokens;

    //Match words or quoted strings using Regex
    std::regex rgx(R"((\"[^\"]+\"|\S+))");
    auto words_begin = std::sregex_iterator(input.begin(), input.end(), rgx);
   auto words_end =  std::sregex_iterator();

   for(auto it = words_begin; it != words_end; ++it){
        std::string token = it->str();

        //if there are quotes we remove them
        if(token.size() >= 2 && token.front() == '\"' && token.back() == '\"'){
            token = token.substr(1, token.size() - 2);
        }
        tokens.push_back(token);
   }

    return tokens;
}

/*
    * ->start of array
    $ -> bulk of string
    +arg
*/
std::string CommandHandler::buildRESPCommand(const std::vector<std::string> &args){
    std::ostringstream oss;
    oss << "*" << args.size() << "\r\n"; //number of arguments

    for(const auto &arg: args) {
        oss << "$" << arg.size() << "\r\n" << arg << "\r\n"; 
    }
    return oss.str();
}