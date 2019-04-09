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
#include <assert.h>
#define SIZEBUFFER 1024

/** fn prototypes*/
void prompt(void);
int listenread(char *);
void get_simple_args(int, char **, char *);
void get_simple_args2(char *);
char** str_split(char* a_str, const char a_delim);

/** fn entry to launch shell program*/
/** this fn allow get data of the client terminal to after process, when it's pass the fn is call newly*/
int main (int argc, char *argv[] __attribute((unused)))
{
	/** pointer used to save data input of the terminal client */
	char *line;
	long int i = 0;
	long int i2 = 0;
	char *argv2[] = {__FILE__, NULL};

        /** launch prompt */
	prompt();

	if (argc == 1)
	{
        	line = malloc(sizeof(char) * SIZEBUFFER + 2);
		if (!line)
			exit(100);
		line[SIZEBUFFER] = '\0';

		/** init the read and write data input of client, it's recursive fn*/
		if(listenread(line))
			printf("get data line >> %s\n", line);
	}

	/** parse the pointer to exec the command*/
	get_simple_args(argc, argv, line);

	/** the memory is unblock*/
	free(line);

	/** call himself, fn recursive */
	/*main(1, argv2);*/
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
void get_simple_args(int argc, char **argv __attribute__((unused)), char *args __attribute__((unused)))
{
	char delim[] = " \n";
	pid_t pid;
	char *envp[] = {"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin",NULL};
	char *command;
	int status;
	int i = 0;
	int existsdelim = 0;

	if (argc == 1)
	{
		while (args[i] != '\0')
			i++;
		command = (char *)strtok(args, delim);

		if (i > 0)
			get_simple_args2((char *)command);
	}
	else if(argc > 1)
		get_simple_args2(argv[1]);
}

void get_simple_args2(char *command)
{
	pid_t pid;
	char *envp[] = {"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin",NULL};
	int status;
	char *_argv[] = {command, NULL};

	pid = fork();
	if (pid == 0)
		if (execve(command, _argv, envp) == -1)
		{
			printf("Error execve\n");
			exit(103);
		}
	else if (pid < 0)
	{
		printf("Error pid < 0\n");
		exit(102);
	}
		do{
			waitpid(pid, &status, 0);
		}while(!WIFEXITED(status) && !WIFSIGNALED(status));
}
