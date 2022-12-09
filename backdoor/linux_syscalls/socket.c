//
// Created by explorer on 2022/6/29.
//
#include <sys/socket.h>
#include <syscall.h>

int socket(int domain, int type, int protocol) {
    return syscaller3(__NR_socket, domain, type, protocol);
}

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    return syscaller3(__NR_connect, sockfd, addr, addrlen);
}