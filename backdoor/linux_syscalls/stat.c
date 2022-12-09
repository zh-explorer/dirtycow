//
// Created by explorer on 2022/6/22.
//

#include <sys/stat.h>
#include "syscall.h"

mode_t umask(mode_t mask) {
    return syscaller1(__NR_umask, mask);
}