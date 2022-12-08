#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "exploit.h"

int main() {
    char *filename = "/foo";
    int fd = open(filename, O_RDONLY);
    struct stat st;
    fstat(fd, &st);

    unsigned char *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);

    printf("map %p\n", map);
    printf("content: %s\n", map);

    struct mem_vec vec;
    vec.address = map;
    vec.data = "fuck";
    vec.size = 4;
    exploit(&vec, 1,  PRTACE_POKEDATA);

    return 0;
}
