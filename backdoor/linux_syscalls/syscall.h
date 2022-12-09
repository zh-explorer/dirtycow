//
// Created by explorer on 2022/6/16.
//

#ifndef SCMAKER_SYSCALL_H
#define SCMAKER_SYSCALL_H

#include "SyscallNumber.h"
#include "sys/types.h"

#ifdef __x86_64__
typedef u_int64_t WORD;
#endif
#ifdef __i386__
typedef u_int32_t WORD;
#endif

WORD syscaller0(long number);

WORD syscaller1(long number, WORD a1);

WORD syscaller2(long number, WORD a1, WORD a2);

WORD syscaller3(long number, WORD a1, WORD a2, WORD a3);

WORD syscaller4(long number, WORD a1, WORD a2, WORD a3, WORD a4);

WORD syscaller5(long number, WORD a1, WORD a2, WORD a3, WORD a4, WORD a5);

// there is not 6 arg syscall in x86
#ifdef __x86_64__

WORD syscaller6(long number, WORD a1, WORD a2, WORD a3, WORD a4, WORD a5, WORD a6);

#endif
#endif //SCMAKER_SYSCALL_H
