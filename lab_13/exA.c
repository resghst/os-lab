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
	return &ret;
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
	int input,unlock;
	//while(1){
		printf("1.exclusive lock(write lock). 2.share lock(readlock).\n");
		scanf(" %d",&input);
		if (input==1){
			if ( fcntl(fd, F_SETLK, file_lock(F_WRLCK, SEEK_SET)) == 0 ){
				printf("Locking file with 'WRLCK' success, enter integer to unlock:\n");
				scanf(" %d",&unlock);
			}
			else{
			}
		}
		else if(input==2){
			if( fcntl(fd, F_SETLK, file_lock(F_RDLCK, SEEK_SET)) == 0 ){
				printf("Locking file with 'RDLCK' success, enter integer to unlock:\n");
				scanf(" %d",&unlock);
			}
			else{
			}
		}
		//fuctl(fb, F_SETLK, file_lock(F_WRLCK, SEEK_SET)); // 0 => lock
		fcntl(fd, F_SETLKW, file_lock(F_UNLCK, SEEK_SET));
	//}
	
	return 0;
}