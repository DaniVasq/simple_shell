#include "shell.h"
void pid_launch(char *command, char **_argv);

/**
 * prompt - function for the print symbol before the user types
 *
 * Return: nothing.
 */
void prompt(void)
{
	/** symbol > */
	putchar(62);
	/** symbol space */
	putchar(32);
}
/**
 * listenread - get char the client terminal & call fn until char is '\n'
 *@buffer: pointer
 * Return: 1 is successful, -1 if error.
 */
long int listenread(char *buffer)
{
	size_t bufsize = SIZEBUFFER;
	size_t c;

	/**fflush(stdin);*/
	c = getline(&buffer, &bufsize, stdin);
	if (!c)
		return (-1);
	return (1);
}
/**
 * get_simple_args - this fn splita the string when space char is found
 *@argc: argument counter
 *@argv: where the arguments are contained
 *@args: arguments
 */
/*void get_simple_args(int argc, char **argv __attribute__((unused)), char *args __attribute__((unused)))*/
void get_simple_args(int argc, char **argv, char *args)
{
	char delim[] = " \n";
	char *command;
	int exists_space = 0;
	int i = 0, t = 0;
	char **options;
	char *argx;
	int j = 0;

	if (argc == 1 && _strlen(args) > 1)
	{
		while (args[i] != '\0')
		{
			if (args[i] == ' ')
				exists_space++;
			i++;
		}
		options = malloc(sizeof(int) * exists_space + 1);
		if (options == NULL)
			exit(107);
		argx = strtok(args, delim);

		while (argx != NULL)
		{
			options[j] = argx;
			argx = strtok(NULL, delim);
			j++;
		}
		command = (char *)strtok(args, delim);
		if (i > 0 && command != NULL)
			pid_launch((char *)command, options);
		free(args);
	}
	/**else if (argc == 2)
	   pid_launch(argv[1], argv);*/
}
/**
 * _error - allows the error message to be printed in shell
 *
 */
void _error(void)
{
	printf("/%s: No such file or directory\n", __FILE__);
}
/**
 * pid_launch - allows shell to be launched
 *@command: the command needed to pass to the machine to perform
 */
void pid_launch(char *command, char **_argv)
{
	pid_t pid;
	char *envp[] = {"", NULL};
	/*char *envp[] = {"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin",NULL};*/
	int status;
	/**char *_argv[] = {command, NULL};*/


	if (strlen(command) > 0)
	{
		/** create id process (parent & child) to launch command*/
		pid = fork();
		if (pid == 0)
			if (execve(command, _argv, envp) == -1)
			{
				_error();
				exit(103);
			}
		else if (pid < 0)
		{
			exit(102);
		}
		/** always wait the pid is kill*/
		do {
			waitpid(pid, &status, 0);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
