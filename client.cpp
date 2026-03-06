#include <iostream>
#include <cstring>
#include <unistd.h>         // close()
#include <arpa/inet.h>      // inet_pton()
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdio>

int main() {
    const char* SERVER_IP = "127.0.0.1";
    const int PORT = 8080;

    char ip[INET_ADDRSTRLEN];
    // Create client socket
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        std::cerr << "Error: failed to create socket\n";
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        std::cerr << "Error: invalid server IP address\n";
        close(sock_fd);
        return 1;
    }

    // Connect to server
    if (connect(sock_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        perror("connect");
        close(sock_fd);
        return 1;
    }

    inet_ntop(AF_INET, &server_addr.sin_addr, ip ,sizeof(ip));
    std::cout << "Connected to server at " << ip << ":" << ntohs(server_addr.sin_port) << " \n";

    //Send Message
    std::string line;
    while(true)
    {
        if(!std::getline(std::cin, line ))
        {
            std::cout<<"\nInput ended (EOF). Closing client...\n";
            break;
        }
        if(line=="/quit")
        {

            std::cout<<"Quitting \n";
            break;
        }
        line+="\n";
        if(send(sock_fd, line.c_str() , line.size() , 0)<0)
        {
            perror("send");
            return 1;
        }
    }    
    close(sock_fd);


    return 0;
}
