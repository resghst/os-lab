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
	char ch[80];
	void *file_memory;

	fd = open("input.txt", O_RDWR, S_IRUSR | S_IWUSR);

	lseek(fd, 1, SEEK_SET);
	write(fd,"",80);

	file_memory = mmap(0, FILE_LENGTH, PROT_WRITE, MAP_SHARED, fd, 0);

	close(fd);
	while(1){
		printf("enter any string\n");
		scanf(" %s", ch);
	 	printf("ch is --%s\n", ch);
		getchar();
		sprintf((char*)file_memory, "%s\n", ch);
		file_memory = file_memory + strlen(ch);
		printf("can use the more command check file.\n");
	}


	munmap((char*)file_memory, FILE_LENGTH);
	return 0;
}