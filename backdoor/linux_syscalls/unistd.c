//
// Created by explorer on 2022/6/16.
//

#include <unistd.h>
#include "syscall.h"

int dup2(int oldfd, int newfd) {
    return syscaller2(__NR_dup2, oldfd, newfd);
}

ssize_t readlink(const char *pathname, char *buf, size_t bufsiz) {
    return syscaller3(__NR_readlink, pathname, buf, bufsiz);
}

pid_t getpid(void) {
    return syscaller0(__NR_getpid);
}


pid_t fork(void) {
    return syscaller0(__NR_fork);
}

void __attribute__ ((__noreturn__)) _exit(int status) {
    syscaller1(__NR_exit, status);
}

pid_t setsid(void) {
    return syscaller0(__NR_setsid);
}


int chdir(const char *path) {
    return syscaller1(__NR_chdir, path);
}

int close(int fd) {
    return syscaller1(__NR_close, fd);
}

int dup(int oldfd) {
    return syscaller1(__NR_dup, oldfd);
}

int execve(const char *filename, char *const argv[], char *const envp[]) {
    return syscaller3(__NR_execve, filename, argv, envp);
}