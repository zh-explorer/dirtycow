//
// Created by explorer on 2022/12/9.
//

#include "vdso_backdoor.h"
#include <sys/auxv.h>

void * get_vdso_base() {
    return (void *) getauxval(AT_SYSINFO_EHDR);
}


// It's hard for support every vdos
// for now, hard code one for ubuntu:16.04
struct mem_vec * get_vdso_patch_vec() {

}
