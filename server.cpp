#include <iostream>
#include <cstring>
#include <unistd.h>         // close()
#include <arpa/inet.h>      // inet_addr()
#include <sys/socket.h>
#include <netinet/in.h>

int main() {
    const int PORT = 8080;

    // Create server socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Error: failed to create socket\n";
        return 1;
    }

    // Allow quick restart of server (reuse address)
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "Warning: setsockopt failed\n";
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket to port
    if (bind(server_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) < 0) {
        std::cerr << "Error: bind failed (is port " << PORT << " already in use?)\n";
        close(server_fd);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 5) < 0) {
        std::cerr << "Error: listen failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << "...\n";
    std::cout << "Day 1 setup successful ✅\n";

    // For Day 1, just wait for one connection and close
    sockaddr_in client_addr{};
    socklen_t client_len = sizeof(client_addr);

    int client_fd = accept(server_fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len);
    if (client_fd < 0) {
        std::cerr << "Error: accept failed\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Client connected!\n";

    close(client_fd);
    close(server_fd);
    return 0;
}
