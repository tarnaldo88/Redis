#include "CLI.h"

//Function to trim whitespace
static std::string trim(std::string &s){
    size_t start = s.find_first_not_of(" \t\n\r\f\v");

    if(start == std::string::npos) return "";

    size_t end = s.find_last_not_of(" \t\n\r\f\v");

    return s.substr(start, end - start + 1);
}

CLI::CLI(const std::string &host, int port) : redisClient(host, port) { }

void CLI::run() {
    if( !redisClient.connectToServer()){
        return;
    }

    std::cout << "Connected to Redis server at " << redisClient.getSocketFd() << "\n";   
    std::string host = "127.0.0.1";
    int port = 6379;
    
    while(true) {
        std::cout << host <<  ":" << port << ">";
        std::cout.flush();
        std::string line;

        if(!std::getline(std::cin, line)) break;

        line = trim(line);

        if(line.empty()) continue;
        if(line == "quit") {
            std::cout << "Exiting. \n";
            break;
        }
    }
}