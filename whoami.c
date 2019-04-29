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
#include <pwd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
     
int  whoami() 
{      
	struct passwd *pw;
	char *user = NULL;

	pw = getpwuid(geteuid());
	if (pw)
	   user = pw->pw_name;
	else if ((user = getenv("USER")) == NULL) {
	   fprintf(stderr, "I don't know!\n");
	   return 1;
	}
	printf("%s\n", user);
	return 0;
}