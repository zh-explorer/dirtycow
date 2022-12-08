//
// Created by explorer on 2022/12/8.
//

#include "unit.h"
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void warning(char *file, char * function,int line,  char * str) {
    fprintf(stderr, "%s:%s:%d error: %s: %s\n",file, function, line, str, strerror(errno));
    exit(-1);
}