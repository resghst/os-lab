#include <dirent.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
	DIR *dp;
	char *dir = "./test";
	struct stat statbuf;
	struct dirent *entry;

	//printf("frgrdsdrgs\n");
	
	if ((dp = opendir(dir)) == NULL){
		return;
	}
	chdir(dir);
	while((entry=readdir(dp))!=NULL){
		lstat(entry->d_name, &statbuf);
		if (strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name, "..")==0)
			continue;
		printf("name %s  [%d]\n",entry->d_name ,S_ISDIR(statbuf.st_mode));
		
	}
	closedir(dp);
	exit(0);

	return 0;
}