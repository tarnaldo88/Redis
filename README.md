# **Redis Client (C++17)**
A lightweight, cross-platform Redis client skeleton in C++ that connects to a Redis server, formats commands using RESP, and parses responses.

## **Features (current)**
Connects to a Redis server over TCP.
Builds commands in RESP format from tokens (CommandHandler).
Parses RESP replies: Simple Strings, Errors, Integers, Bulk Strings, Arrays (ResponseParser).
Cross-platform sockets:
Windows: Winsock2
Linux: POSIX sockets
Minimal CLI scaffold (connection and groundwork in place for REPL/one-shot).
Note: The interactive REPL is scaffolded and will be expanded (parsing input, sending commands, printing parsed replies).

## **Technologies**
C++17
Sockets: Winsock2 (Windows) / POSIX (Linux)
Build: GNU Make (MinGW/MSYS2 on Windows, GNU Make + g++ on Linux)
Parsing helpers: <regex>, <sstream>

## **Project Structure**
Client/
main.cpp
 — entry point; initializes Winsock on Windows and runs CLI
CLI.h/.cpp — CLI scaffold
RedisClient.h/.cpp — TCP connection logic, portable socket type (socket_t), error handling
CommandHandler.h/.cpp — tokenization and RESP command builder
ResponseParser.h/.cpp — RESP response parser
Makefile
 — portable build for Linux and Windows (MinGW/MSYS2)
README.md
 — this file

## **Build and Run**
Prerequisites:

Running Redis server (default: 127.0.0.1:6379)
C++ toolchain
Windows (MSYS2/MinGW):

Open “MSYS2 MinGW64” shell.
Install toolchain (if needed):
pacman -S --needed mingw-w64-x86_64-gcc make
Build:
make
Run:
./bin/my_redis_cli.exe -h 127.0.0.1 -p 6379
Linux:

Ensure g++ and make are installed.
Build:
make
Run:
./bin/my_redis_cli -h 127.0.0.1 -p 6379

### **Notes**

On Windows, linking uses -lws2_32. On Linux, no extra socket libs are required.
The build outputs to bin/, objects to build/.

## **Usage**
Current behavior: attempts to connect to the specified host/port and prints a confirmation on success.
Next step: enable interactive REPL to read commands (e.g., SET key val, GET key), send them via RESP, and print parsed replies.

## **Troubleshooting**
Windows “connect() failed” with a Winsock error:
Verify Redis is running and not blocked by firewall.
Ensure you ran the program in an MSYS2 MinGW shell (not plain CMD/PowerShell for make).
Linux “Connection refused”:
Ensure redis-server is running and accepting connections on the given port.
Link errors on Windows:
Confirm you’re using MinGW g++ and the build includes -lws2_32 (the Makefile handles this automatically).

## **Roadmap**
Implement CLI REPL (readline loop, history, help/quit).
Wire CommandHandler and ResponseParser to CLI for end-to-end command execution.
Add one-shot command mode (parse args into a single command).
Robust I/O: partial reads/writes, buffering.
Tests and benchmarking.