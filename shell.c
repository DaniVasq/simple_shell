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
void get_data_line(void);
int listenread(char *);
void get_simple_args(void);

/** fn entry to launch shell program*/
int main(void)
{
	/** simply and power fn that listen of and process the features the program*/
	get_data_line();
	return (0);
}
/** this fn allow get data of the client terminal to after process, when it's pass the fn is call newly*/
void get_data_line(void)
{
	/** pointer used to save data input of the terminal client */
	char *line;

	line = malloc(sizeof(char) * SIZEBUFFER + 1);
	if (!line)
		exit(100);
	line[SIZEBUFFER] = '\0';

	/** launch prompt */
	prompt();

	/** init the read and write data input of client, it's recursive fn*/
	if(listenread(line))
		printf("get data line >> %s\n", line);

	/** parse the pointer to exec the command*/
	get_simple_args();

	/** the memory is unblock*/
	free(line);

	/** call himself, fn recursive */
	get_data_line();
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
int listenread(char *line)
{
	/** the var that receive a char and save into pointer*/
	int c;

	/** the client write into terminal */
	c = getchar();
	/** statement that exit when it reaches the end file */
	if(c == EOF)
		exit(101);
	/** when find end line the same type key enter or return */
	else if(c == '\n')
	{
		*line = '\0';
		return 1;
	}
	/** save the char into var*/
	*line = c;
	/** the pointer is moved to the next position and call himself*/
	listenread(line + 1);
}
/** 
* Description: this fn allow split the string when find the space char
*/
void get_simple_args(void)
{
	
}
