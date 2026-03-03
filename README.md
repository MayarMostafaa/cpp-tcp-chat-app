# C++ TCP Chat Application (Client-Server)

A terminal-based chat application in C++ using TCP sockets and multithreading on Linux.

## Planned Features
- TCP server and client
- Multiple client connections
- Multithreaded server
- Message broadcasting
- Basic error handling
- Thread-safe shared client handling (mutex)

## Tech Stack
- C++17
- POSIX sockets (Linux)
- std::thread / std::mutex
- Git + GitHub

## Status
In progress (Day 1 setup)

## Build (planned)
```bash
g++ -std=c++17 -pthread server.cpp -o server
g++ -std=c++17 client.cpp -o client
