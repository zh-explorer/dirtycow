#include "syscall.h"

#ifdef __x86_64__

WORD syscaller0(long number) {
    WORD n = 0;
    __asm__ __volatile__ (
            "syscall\n\t"
            : "=a" (n)
            : "a" (number));
    return n;
}


WORD syscaller1(long number, WORD a1) {
    WORD n = 0;
    __asm__ __volatile__ (
            "syscall\n\t"
            : "=a" (n)
            : "a" (number), "D" (a1));
    return n;
}

WORD syscaller2(long number, WORD a1, WORD a2) {
    WORD n = 0;
    __asm__ __volatile__ (
            "syscall\n\t"
            : "=a" (n)
            : "a" (number), "D" (a1), "S" (a2));
    return n;
}

WORD syscaller3(long number, WORD a1, WORD a2, WORD a3) {
    WORD n = 0;
    __asm__ __volatile__ (
            "syscall\n\t"
            : "=a" (n)
            : "a" (number), "D" (a1), "S" (a2), "d" (a3));
    return n;
}

WORD syscaller4(long number, WORD a1, WORD a2, WORD a3, WORD a4) {
    WORD n = 0;
    WORD aa4 = a4;
    __asm__ __volatile__ (
            "push %5\n\t"
            "pop %%r10\n\t"
            "syscall\n\t"
            : "=a" (n)
            : "a" (number), "D" (a1), "S" (a2), "d" (a3), "r" (aa4));
    return n;
}

WORD syscaller5(long number, WORD a1, WORD a2, WORD a3, WORD a4, WORD a5) {
    WORD n = 0;
    WORD aa4 = a4;
    WORD aa5 = a5;
    __asm__ __volatile__ (
            "push %6\n\t"
            "push %5\n\t"
            "pop %%r10\n\t"
            "pop %%r8\n\t"
            "syscall\n\t"
            : "=a" (n)
            : "a" (number), "D" (a1), "S" (a2), "d" (a3), "r" (aa4), "r" (aa5));
    return n;
}

WORD syscaller6(long number, WORD a1, WORD a2, WORD a3, WORD a4, WORD a5, WORD a6) {
    WORD n = 0;
    WORD aa4 = a4;
    WORD aa5 = a5;
    WORD aa6 = a6;
    __asm__ __volatile__ (
            "push %7\n\t"
            "push %6\n\t"
            "push %5\n\t"
            "pop %%r10\n\t"
            "pop %%r8\n\t"
            "pop %%r9\n\t"
            "syscall\n\t"
            : "=a" (n)
            : "a" (number), "D" (a1), "S" (a2), "d" (a3), "r" (aa4), "r" (aa5), "r" (aa6));
    return n;
}

#endif

#ifdef __i386__

WORD syscaller0(long number)
{
    WORD n = 0;
    __asm__ __volatile__(
            "int $0x80\n\t"
            : "=a"(n)
            : "a" (number));
    return n;
}

WORD syscaller1(long number,  WORD a1)
{
    WORD n = 0;
    __asm__ __volatile__(
            "int $0x80\n\t"
            : "=a"(n)
            : "a" (number), "b" (a1));
    return n;
}

WORD syscaller2(long number,  WORD a1, WORD a2)
{
    WORD n = 0;
    __asm__ __volatile__(
            "int $0x80\n\t"
            : "=a"(n)
            : "a" (number), "b" (a1), "c" (a2));
    return n;
}

WORD syscaller3(long number, WORD a1, WORD a2, WORD a3)
{
    WORD n = 0;
    __asm__ __volatile__(
            "int $0x80\n\t"
            : "=a"(n)
            : "a" (number), "b" (a1), "c" (a2), "d" (a3));
    return n;
}

WORD syscaller4(long number, WORD a1, WORD a2, WORD a3, WORD a4)
{
    WORD n = 0;
    __asm__ __volatile__(
            "int $0x80\n\t"
            : "=a"(n)
            : "a" (number), "b" (a1), "c" (a2), "d" (a3), "S" (a4));
    return n;
}

WORD syscaller5(long number, WORD a1, WORD a2, WORD a3, WORD a4, WORD a5)
{
    WORD n = 0;
    __asm__ __volatile__(
            "int $0x80\n\t"
            : "=a"(n)
            : "a" (number), "b" (a1), "c" (a2), "d" (a3), "S" (a4), "D" (a5));
    return n;
}

WORD syscaller6(long number, WORD a1, WORD a2, WORD a3, WORD a4, WORD a5, WORD a6)
{
    WORD n = 0;
    __asm__ __volatile__(
            "push %%ebp\n\t"
            "push %7\n\t"
            "pop %%ebp\n\t"
            "int $0x80\n\t"
            "pop %%ebp\n\t"
            : "=a"(n)
            : "a" (number), "b" (a1), "c" (a2), "d" (a3), "S" (a4), "D" (a5), "m"(a6));
    return n;
}

#endif