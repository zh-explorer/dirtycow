//
// Created by explorer on 2022/6/22.
//

#include "signal.h"

#include <string.h>
#include <errno.h>
#include <limits.h>

int sigemptyset(sigset_t *set) {
    set->__val[0] = 0;
    if (sizeof(long) == 4 || _NSIG > 65) set->__val[1] = 0;
    if (sizeof(long) == 4 && _NSIG > 65) {
        set->__val[2] = 0;
        set->__val[3] = 0;
    }
    return 0;
}

int sigfillset(sigset_t *set) {
#if ULONG_MAX == 0xffffffff
    set->__val[0] = 0x7ffffffful;
    set->__val[1] = 0xfffffffcul;
    if (_NSIG > 65) {
        set->__val[2] = 0xfffffffful;
        set->__val[3] = 0xfffffffful;
    }
#else
    set->__val[0] = 0xfffffffc7ffffffful;
    if (_NSIG > 65) set->__val[1] = 0xfffffffffffffffful;
#endif
    return 0;
}


int sigaddset(sigset_t *set, int sig) {
    unsigned s = sig - 1;
    if (s >= _NSIG - 1 || sig - 32U < 3) {
        errno = EINVAL;
        return -1;
    }
    set->__val[s / 8 / sizeof *set->__val] |= 1UL << (s & 8 * sizeof *set->__val - 1);
    return 0;
}

int sigdelset(sigset_t *set, int sig) {
    unsigned s = sig - 1;
    if (s >= _NSIG - 1 || sig - 32U < 3) {
        errno = EINVAL;
        return -1;
    }
    set->__val[s / 8 / sizeof *set->__val] &= ~(1UL << (s & 8 * sizeof *set->__val - 1));
    return 0;
}

int sigismember(const sigset_t *set, int sig) {
    unsigned s = sig - 1;
    if (s >= _NSIG - 1) return 0;
    return !!(set->__val[s / 8 / sizeof *set->__val] & 1UL << (s & 8 * sizeof *set->__val - 1));
}


int sigaction(int sig, const struct sigaction *restrict sa, struct sigaction *restrict old) {
    unsigned long set[_NSIG / (8 * sizeof(long))];

    if (sig - 32U < 3 || sig - 1U >= _NSIG - 1) {
        errno = EINVAL;
        return -1;
    }
    extern int rt_sigaction(int signum, const struct sigaction *act, struct sigaction *oldact, size_t sigsetsize);
    int r = rt_sigaction(sig, sa, old, _NSIG / 8);
    return r;
}

sighandler_t signal(int signum, sighandler_t handler)
{
    struct sigaction sa_old, sa = { .handler = handler, .flags = SA_RESTART };
    if (sigaction(signum, &sa, &sa_old) < 0)
        return SIG_ERR;
    return sa_old.handler;
}