#include <stdio.h>
#include <fcntl.h> // for open(), close(), read()
#include <string.h> // for memset()
#include <sys/select.h> // for FD_*, select()
#include <limits.h> // for PIPE_BUF
/*
struct timeval{
	long tv_sec; // seconds
	long tv_usec; // and microseconds
}*/

int main(){
	char buffer[9999];

	fd_set tmpset; 
	int fd1 = open("fifo1", O_RDWR);
	int fd2 = open("fifo2", O_RDWR);
	int ready;
	int maxfd1;

	struct timeval tv;
	tv.tv_sec = (1);
	tv.tv_usec = (500000);

	if(fd1>fd2){ maxfd1=fd1;}
	else{ maxfd1=fd2; }

	while(1){
		FD_ZERO(&tmpset);
	  	FD_SET(fd1,&tmpset);
	  	FD_SET(fd2,&tmpset);
		memset(&buffer, 0, PIPE_BUF);
		if((ready = select(maxfd1+1, &tmpset, NULL, NULL, &tv)) < 0){ // Failure
			printf("error\n");
		}else if(ready == 0){ // Timeout
			//printf("Timeout\n");
		}else{ // Ready
			if(FD_ISSET(fd1, &tmpset)){ // fd1 is readable
				printf("Device 1 can read.\n");
				read(fd1, &buffer, PIPE_BUF);
				printf("%s\n", buffer);
			}
			if(FD_ISSET(fd2, &tmpset)){ // fd2 is readable
				printf("Device 2 can read.\n");
				read(fd2, &buffer, PIPE_BUF);
				printf("%s\n", buffer);
			}
		}
	}
	
	return 0;
}