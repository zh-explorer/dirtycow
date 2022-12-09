//
// Created by explorer on 2022/6/16.
//

#include <string.h>

int strcmp(const char *s1, const char *s2) {
    unsigned int i;
    for (i = 0; s1[i] != 0 && s1[i] == s2[i]; i++);
    if (s1[i] == s2[i]) {
        return 0;
    } else {
        return s1[i] < s2[i] ? -1 : 1;
    }
}