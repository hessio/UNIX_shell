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
#include <fcntl.h> // for open
#include <unistd.h> // for close
void execute(char** cmds){
	pid_t pid = fork();
	if(pid == -1){
		return;
	}
	else if(pid == 0){
		printf("here: %c", cmds[0][0]);
		if(execvp(cmds[0], cmds) == -1){
			printf("Couldn't execute command!\n");
		}
		exit(0);
	}
	else{
		wait(NULL); 
		return;
	}
}

void execute_to_output_file(char** cmds, char* fileName)
{
	
	int fd = open(fileName, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	int stdout = dup(1);
    close(1);
    dup(fd);
    close(fd);
	pid_t pid = fork();
	if(pid == -1){
		dup2(stdout, 1);
		close(stdout);
		return ;
	}
	else if(pid == 0){
		if(execvp(cmds[0], cmds) == -1){
			printf("Couldn't execute command!\n");
		}
		dup2(stdout, 1);
		close(stdout);
		exit(0);
	}
	else{
		wait(NULL); 
		dup2(stdout, 1);
		close(stdout);
		return;
	}
}
