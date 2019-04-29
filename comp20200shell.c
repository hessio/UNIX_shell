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

void ls(char **parsed){
	execute(parsed);
}

void makedir(char** parsed)
{
	execute(parsed);
}

void rm_dir(char** parsed)
{
	execute(parsed);
}

char* help(){
	char* string = malloc(sizeof(char) * 10000 ) ;
	strcat(string, "**********************************************\n*\tWelcome to Patrick's terminal.\t     ");
	strcat(string, "*\n**********************************************\nHere are your options of commands:\n\n");
	strcat(string, "'help' - will diplay help message\n");
	strcat(string, "'exit' - will end the command prompt\n'ls' - will display the current directory of folders\n");
	strcat(string, "'cd' - will allow you to change your current working directory.\n");
	strcat(string, "'whoami' - will print the user name of the current user you are logged in as in the terminal.\n");
	strcat(string, "'mkdir' - will create a new directory.\n");
	strcat(string, "'echo' - will print the subsequent text to the terminal window.\n");
	strcat(string, "'cat' - will print the contents of the subsequent file to the terminal window.\n");
	return string;
}

void cmdEcho(char **words){
	int i = 1;
	while(words[i] != NULL){
		printf("%s ", words[i]);
		i++;
	}
	printf("\n");
}

void cmdSleep(char **words){
	execute(words);
}

void cat(char** words)
{
	FILE *f = fopen(words[1], "r");
	char ch, file_name[25];
	if (f == NULL)
	{
		perror("Error while opening the file.\n");
		exit(EXIT_FAILURE);
	}
	while((ch = fgetc(f)) != EOF)
    	printf("%c", ch);
    printf("\n");
   fclose(f);
}

int commandHandling(char** words){
	char **find = words;
	int j = 0;
	int redirect = 0;
	while(find[j] != NULL)
	{
		if(strcmp(find[j], ">") == 0)
			redirect = j;
		++j;	
	}
	*words = words[0];
	if(!redirect)
	{
		int numOfCmds = 10, i = 0, cmdSwitch = 0;
		char* listOfCmds[numOfCmds];
		
		listOfCmds[0] = "exit";
		listOfCmds[1] = "cd";
		listOfCmds[2] = "ls";
		listOfCmds[3] = "help";
		listOfCmds[4] = "pwd";
		listOfCmds[5] = "echo";
		listOfCmds[6] = "sleep";
		listOfCmds[7] = "whoami";
		listOfCmds[8] = "mkdir";
		listOfCmds[9] = "cat";
		listOfCmds[10] = "rmdir";
		listOfCmds[11] = NULL;
		
		while(listOfCmds[i] != NULL){
			if(strcmp(listOfCmds[i], words[0]) == 0){
				cmdSwitch = i + 1;
				break;
			}
			i++;
		}
		
		switch(cmdSwitch){
			case 1:
				exit(0);
				break;
			case 2:
				changedir(words);
				printDir();
				break;
			case 3:
				ls(words);
				break;
			case 4:
				printf("%s", help());
				break;
			case 5:
				printDir();
				break;
			case 6:
				cmdEcho(words);
				break;
			case 7:
				cmdSleep(words);
				break;
			case 8:
				whoami();
				break;
			case 9:
				makedir(words);
				break;
			case 10:
				cat(words);
				break;
			case 11:
				rm_dir(words);
				break;
			default:
				break;
		}
	}
	else
	{	
		FILE *f = fopen(words[redirect+1], "w");
		
		char** cmds = malloc(sizeof(char*));
		char output[1000];
		int numOfCmds = 7, i = 0, cmdSwitch = 0;
		char* listOfCmds[numOfCmds];
		
		listOfCmds[0] = "exit";
		listOfCmds[1] = "cd";
		listOfCmds[2] = "ls";
		listOfCmds[3] = "help";
		listOfCmds[4] = "pwd";
		listOfCmds[5] = "echo";
		listOfCmds[6] = "sleep";
		listOfCmds[7] = NULL;
		
		while(listOfCmds[i] != NULL){
			if(strcmp(listOfCmds[i], words[0]) == 0){
				cmdSwitch = i + 1;
				break;
			}
			i++;
		}
		
		switch(cmdSwitch){
			case 1:
				exit(0);
				strcpy(output, "Bye");
				break;
			case 2:
				changedir(words);
				char cwd[1024];
				getcwd(cwd, sizeof(cwd));
				strcpy(output, cwd);
				break;
			case 3:
				for(int i = 0; i < redirect; ++i)
				{
					cmds[i] = words[i];
				}
				execute_to_output_file(cmds, words[redirect+1]);
				break;
			case 4:
				strcpy(output, help());
				break;
			case 5:
				printDir();
				break;
			case 6:
				cmdEcho(words);
				break;
			case 7:
				cat(words);
				break;
			default:
				break;
		}
		
		fprintf (f, "%s", output);
		fclose(f);
	}
	return 1;
}

char* takeInput()
{
	char *line = NULL;
    size_t linelen;
    int characters = 1;
	while( characters ){
    	getline(&line, &linelen, stdin);
    	if(strlen(line) > 2){
    		break;
    	}
    	if(strlen(line) == 0){
    		exit(0);
    	}
    	if(strcmp(line, "\n") == 0){
    		printf(" error: please enter a command!\n");
    	}
    	line = (char*)malloc(sizeof(char*));
	}
	return line;
}

char** splitInput(char *datas) 
{
	char **output_str = malloc(sizeof(char*));
	int count = 0;
	char* temp;
	
	temp = strtok(datas, " \n");
	
	while(temp != NULL){
		output_str[count] = temp;
                count++;
		output_str = realloc(output_str, (count + 1) * sizeof(char*));
		temp = strtok(NULL, " \n");
	}

	return output_str;
}

void loop(){
	char line[100];
	char* lines = malloc( 100 * sizeof(char*));
	char** args = malloc(sizeof(char*));
	int status = 1;
	time_t rawtime;
        struct tm *info;
        char buffer[80];

	while(status){
		time( &rawtime );
		info = localtime( &rawtime );
		strftime(buffer,80,"%x - %I:%M%p", info);
		printf("%s# ", buffer);
		lines = takeInput();
		if(strlen(lines) > 0){
			memcpy(line, lines, strlen(lines) + 1);
			free(lines);
			args = splitInput(line);
			status = commandHandling(args);
		}
	}
}

void signalHandler(int signum){
	loop();
}

int main(int argc, char *argv[]){
    clear();
    signal(SIGINT, signalHandler);
	loop();

	return EXIT_SUCCESS;
}
