#include <iostream>
#include <cstring>
#include <unistd.h>         // close()
#include <arpa/inet.h>      // inet_pton()
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    const char* SERVER_IP = "127.0.0.1";
    const int PORT = 8080;

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
        std::cerr << "Error: connect failed (is the server running?)\n";
        close(sock_fd);
        return 1;
    }

    std::cout << "Connected to server at " << SERVER_IP << ":" << PORT << " ✅\n";

    close(sock_fd);
    return 0;
}
