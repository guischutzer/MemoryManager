
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "utils.h"

int main() {
    char*  input, shell_prompt[MAXCHAR];
    char** argv;

    while(1) {

	    snprintf(shell_prompt, sizeof(shell_prompt), "[%s] ", getcwd(NULL, 1024));

	    input = readline(shell_prompt);
	        
	    add_history(input);

    	if (fork() != 0) {

	        waitpid(-1, NULL, 0);

	        free(input);

	    } else {

	    	argv = tokenize(input);

	    	if (strcmp(argv[0], "pwd") == 0) {
	    		printf("%s\n", getcwd(NULL, 1024));
	    	}
	    	else if (strcmp(argv[0], "cd") == 0) {
	    		chdir(argv[1]);
	    	}
	    	else {
	    		execve(argv[0], argv, NULL);
	    	}

	    	free(argv);

	    }
    }
    return 0;
}