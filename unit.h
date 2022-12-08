//
// Created by explorer on 2022/12/8.
//

#ifndef DIRTYCOW_UNIT_H
#define DIRTYCOW_UNIT_H
#include <stdio.h>

void warning(char *file, char * function,int line,  char * str);

#define warn(str) warning(__FILE__, __FUNCTION__, __LINE__, (str))

#endif //DIRTYCOW_UNIT_H
