//
// Created by explorer on 2022/12/9.
//

#ifndef DIRTYCOW_VDSO_BACKDOOR_H
#define DIRTYCOW_VDSO_BACKDOOR_H

#include "dirtycow.h"

// hard code vdso size
#define VDSO_SIZE 0x2000

struct mem_vec * get_vdso_patch_vec();

#endif //DIRTYCOW_VDSO_BACKDOOR_H
