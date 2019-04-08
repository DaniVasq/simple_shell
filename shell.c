/**
 * Description: Hi, Laura, this code pretend help to work of the team, allow show the each features, and internal process about the program the shell to get ahead the program, by Fesus Rocuts
 */
/** the minimal headers */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#define SIZEBUFFER 1024

/** fn prototypes*/
void prompt(void);
int listenread(char *);
void get_simple_args(char *args);

/** fn entry to launch shell program*/
/** this fn allow get data of the client terminal to after process, when it's pass the fn is call newly*/
int main (int argc, char *argv[] __attribute((unused)))
{
	/** pointer used to save data input of the terminal client */
	char *line;
	char delim[] = " ";
	char *args;
	/**char *argsv[1] = {""};*/

        /** launch prompt */
	prompt();

	if (argc == 1)
	{
        line = malloc(sizeof(char) * SIZEBUFFER + 1);
	if (!line)
		exit(100);
	line[SIZEBUFFER] = '\0';

	/** init the read and write data input of client, it's recursive fn*/
	if(listenread(line))
		printf("get data line >> %s\n", line);
	args = strtok(line, delim);
	printf("%s\n", args);
	}

	/** parse the pointer to exec the command*/
	/**get_simple_args(args);*/

	/** the memory is unblock*/
	free(line);

	/** call himself, fn recursive */
	/*main(1, NULL);*/
	return (1);
}
/** Description: this fn allow print symbol or mesage before that user write*/
void prompt(void)
{
	/** symbol > */
	putchar(62);
	/** symbol space */
	putchar(32);
}
/** Description; this fn allow get char the client terminal and call me fn until char is '\n'*/
int listenread(char *buffer)
{
	size_t bufsize = SIZEBUFFER;
	size_t c;

	c = getline(&buffer, &bufsize, stdin);
	if (!c)
		return (-1);
	return (1);
}
/**
* Description: this fn allow split the string when find the space char
*/
void get_simple_args(char *args __attribute__((unused)))
{

}
