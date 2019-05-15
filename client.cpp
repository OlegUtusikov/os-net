#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string>
#include <stdio.h>
#include <iostream>

void print_error(const std::string &msg) {
    perror(msg.c_str());
    exit(EXIT_FAILURE);
}

int main(int argc, char** argv) {
    if (argc == 0 || argc > 2) {
        std::cerr << "Incorrect count of arguments" << std::endl;
    }
    const char* host_name = argc == 1 ? argv[0] : argv[1];
    struct hostent *server;
    int socket_fd;
    socket_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (socket_fd < 0) {
        print_error("ERROR opening socket");
        return 0;
    }

    server = gethostbyname(host_name);
    if (server == nullptr) {
        print_error("ERROR, no such host");
        close(socket_fd);
        return 0;
    }

    struct sockaddr_in server_addr{};
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    memcpy(reinterpret_cast<char*>(&server_addr.sin_addr.s_addr), static_cast<char*>(server->h_addr), server->h_length);
    server_addr.sin_port = htons(8888);

    if (connect(socket_fd, reinterpret_cast<sockaddr*>(&server_addr), sizeof(server_addr)) == -1) {
        print_error("ERROR connect a socket");
        close(socket_fd);
        return 0;
    }
    char* msg = "hi!";
    if(send(socket_fd, "", 1, 0) == -1) {
        print_error("bad!");
        close(socket_fd);
    }

    char buf[1024];
    if (recv(socket_fd, &buf, 1024, 0) == -1) {
        print_error("Can't read!");
    }
    std::cout << buf << std::endl;

    return 0;
}