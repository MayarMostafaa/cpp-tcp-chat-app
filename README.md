# Multithreaded TCP Chat App (C++ / Linux)

A terminal-based TCP client/server chat application written in C++17 on Linux.  
The server accepts multiple clients concurrently using threads and broadcasts messages to all connected clients.  
Shared state (connected client sockets) is protected using a mutex for thread safety.

## Features
- TCP server (`socket` → `bind` → `listen` → `accept`)
- TCP client (`socket` → `connect`)
- Multiple clients supported concurrently (thread-per-client model)
- Broadcast messages: when one client sends, all other clients receive
- Sender prefix in broadcasts: `[ip:port] message`
- Safe client list handling with `std::mutex` + `std::lock_guard`
- Clean disconnect handling (removes disconnected clients from list)

## Requirements
- Linux (tested on Ubuntu)
- `g++` with C++17 support

## Build
```bash
make
