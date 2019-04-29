#define clear() printf("\033[H\033[J")
     
int  who_am_i();

void printDir();

void execute(char** cmds);

void execute_to_output_file(char** cmds, char* fileName);

void signalHandler(int);

void changedir(char **words);