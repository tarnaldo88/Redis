/*
Things to implement:
1. Command Line arg parsing
    -h <host> =p <port> default: 127.0.0.1 6379
    if no arguments, launch interactive REPL mode

2. Object-Oriented Programming
    RedisClient, CommandHandler, ResponseParser, CLI

3. Establish TCP Connection to Redis (RedisCLient)
    Berkeley sockets to open TCP connection
    IPv4 and IPv6 'getaddrinfo

4. Parsing & Command Formatting (CommandHandler)
    Split user input (tokenize and handle)
    Convert commands into RESP format:
        (examples)
        *3\r\n
        $3\r\nSET\r\n
        $5\r\nvalue\r\n


5. Handling Redis Responses (ResponseParser)
    Read server responses and parses RESP types
    +OK, -Error, :100, $5\r\nhello -> Bulk string 
    *2\r\n$3\r\nfoo\r\n$3\r\nbar -> Array response
    
6. Implement Interactive REPL (CLI)
    Run loop: UserInput, valis redis commands, send commands to the server, display parsed response
    Support: help, quit

7. main.cpp: parse command-line args, instantiate CLI and launch in REPL mode.

Socket Programming
Protocol Handling
OOP principles
CLI development

*/