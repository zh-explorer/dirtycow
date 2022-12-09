//
// Created by explorer on 2022/6/22.
//
#include <sys/types.h>
#include <fcntl.h>
#include <stdarg.h>
#include "syscall.h"

int open(const char *filename, int flags, ...) {
    mode_t mode = 0;
    va_list ap;
    va_start(ap, flags);
    mode = va_arg(ap, mode_t);
    va_end(ap);

    return syscaller3(__NR_open, filename, flags, mode);
}