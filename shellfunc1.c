#include "shell.h"
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
int listenread(char *buffer)
{
	size_t bufsize = SIZEBUFFER;
	ssize_t c;

	/**fflush(stdin);*/
	c = getline(&buffer, &bufsize, stdin);
	if (c == EOF)
		return (-1);
	else if (_strcmp(buffer, "exit") == 10)
		return (-1);
	return (1);
}
/**
 * get_simple_args - this fn splits the string when space char is found
 *@argc: argument counter
 *@argv: where the arguments are contained
 *@args: arguments
 *@_path: path
 */
void get_simple_args(int argc, char **argv, char *args, char **_path)
{
	char delim[] = " \n";
	char **options;
	char *argx;
	int j = 0;
	int args_max = 255;
	(void)_path;
	/*ARG_MAX*/

	if (argc == 1)
	{
		if ((int)args[0] == 10)
			free(args);
		else
		{
			options = malloc(sizeof(char *) * args_max);
			if (options == NULL)
			{
				free(options);
				exit(111);
			}
			argx = strtok(args, delim);
			while (argx != NULL)
			{
				options[j] = argx;
				argx = strtok(NULL, delim);
				j++;
			}
			options[j] = NULL;
			/*if (update_cmd(options, _path))*/
			    pid_launch(options);
			free(args);
			free(options);
		}
	}
	else if (argc >= 2)
	{
		args_pop(argv);
		/*update_cmd(argv, _path);*/
		pid_launch(argv);
	}
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
 *
 *@_argv: argument container
 */
void pid_launch(char **_argv)
{
	pid_t pid;
	char *envp[] = {"", NULL};
	int status;
	/** create id process (parent & child) to launch command*/
	pid = fork();
	if (pid == 0)
	{
		if (execve(_argv[0], _argv, envp) == -1)
		{
			_error();
			exit(103);
		}
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




