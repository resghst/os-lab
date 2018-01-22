#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
/*
struct flock
{
	short l_type;
	short l_whence;
	off_t l_start;
	off_t l_len;
	pid_t l_pid;
};*/


struct flock* file_lock(short type, short whence){
	static struct flock ret;
	short l_type = type;
	short l_whence = whence;
	off_t l_start = 0;
	off_t l_len = 0;
	return &ret;
}

int main(int argc, char const *argv[])
{
	int fd = open("mandlock.txt",O_RDWR|O_APPEND);
	int input,unlock, k;
	//while(1){
		printf("1.exclusive lock(write lock). 2.share lock(readlock). 3.not use lock\n");
		scanf(" %d",&input);
		if (input==1){
			if (fcntl(fd, F_SETLK, file_lock(F_WRLCK, SEEK_SET)) == 0){
				printf("Locking file with 'WRLCK' fail, another process lock it.\n");
			}
			else{
				printf("success 1\n");
			}
		}
		else if(input==2){
			//printf("%d\n",fcntl(fd, F_SETLK, file_lock(F_RDLCK, SEEK_SET)));
			if( fcntl(fd, F_SETLK, file_lock(F_RDLCK, SEEK_SET)) == 0){
				printf("Locking file with 'RDLCK' fail, another process lock it.\n");
			}
			else{
				char buff[111];
				size_t bytes_read = read(fd, buff, 110);
				puts(buff);
				printf("success 2\n");
			}
		}
		else if(input==3){
			char buff[111];
			size_t bytes_read = read(fd, buff, 110);
			puts(buff);
			printf("success 3\n");
		}
		fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
		//fuctl(fb, F_SETLK, file_lock(F_WRLCK, SEEK_SET)); // 0 => lock	
	//}
	return 0;
}