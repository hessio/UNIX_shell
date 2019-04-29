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

void changedir(char **words){
	if(chdir(words[1]) != 0){
		perror("Error: ");
	}
	else{
		chdir(words[1]);
	}
}