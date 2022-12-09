//
// Created by explorer on 2022/6/22.
//

int *__errno_location(void) {
    static int _errno;
    return &_errno;
}