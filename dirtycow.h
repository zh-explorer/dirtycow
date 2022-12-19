//
// Created by explorer on 2022/12/9.
//

#ifndef DIRTYCOW_DIRTYCOW_H
#define DIRTYCOW_DIRTYCOW_H
struct mem_vec {
    int *address;
    unsigned char *data;
    unsigned int size;
};

enum exploit_type {
    PROC_SELF_MEM,
    PTRACE,
};
#endif //DIRTYCOW_DIRTYCOW_H
