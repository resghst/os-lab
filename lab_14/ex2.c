#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#define FILE_LENGTH 0x01

int main(int argc, char const *argv[])
{
    int fd, count, i;
    char ch[9999];
    void *file_memory;
    int start = atoi(argv[2]);
    int end   = atoi(argv[3]);
    fd = open("input.txt", O_RDWR, S_IRUSR | S_IWUSR);

    file_memory = mmap(0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);

    close(fd);
    //file_memory = file_memory + start;
    sscanf((char*)file_memory, "%s", ch);
    printf("%s\n", ch);
    for (i = start; i <= end; i++){
        printf("%c", ch[i]);
    }
    //printf("%s", ch);
    printf("\n");

    munmap((char*)file_memory, FILE_LENGTH);
    return 0;
}