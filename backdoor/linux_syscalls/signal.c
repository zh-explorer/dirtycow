//
// Created by explorer on 2022/6/22.
//

#include <signal.h>

#include "syscall.h"

int rt_sigaction(int signum, const struct sigaction *act,
                 struct sigaction *oldact, size_t sigsetsize) {
    return syscaller4(__NR_rt_sigaction, signum, act, oldact, sigsetsize);
}