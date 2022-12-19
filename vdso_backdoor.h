//
// Created by explorer on 2022/12/9.
//

#ifndef DIRTYCOW_VDSO_BACKDOOR_H
#define DIRTYCOW_VDSO_BACKDOOR_H

#include "dirtycow.h"

unsigned int get_vdso_patch_vec(struct mem_vec ** vecs_p, unsigned int * size, unsigned char * shellcode, unsigned int shellcode_size);

unsigned int build_shellcode(unsigned char ** shellcode_p, unsigned int * shellcode_size_p, unsigned int target_ip, unsigned short target_port);

#endif //DIRTYCOW_VDSO_BACKDOOR_H
