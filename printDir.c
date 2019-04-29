#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<signal.h>
#include<stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>
#include"shell.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close

void printDir()
{
	char cwd[1024];
	pid_t pid = fork();

	if(pid == -1){
		return;
	}
	else if(pid == 0){
		if(getcwd(cwd, sizeof(cwd)) == NULL){
			printf("Couldn't execute command!\n");
		}
		printf("\nDir: %s ", cwd);
		printf("\n\n\n");
	}
	else{
		wait(NULL); 
		return;
	}
}