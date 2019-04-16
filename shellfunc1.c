#include "shell.h"
/**
 * prompt - function for the print symbol before the user types
 *
 * Return: nothing.
 */
void prompt(_track_shell *raw)
{
	raw->countprocess++;
	if (strcmp(raw->mode, "interactive") == 0)
	{
        	/** symbol > */
        	putchar(62);
        	/** symbol space */
        	putchar(32);
        }
}
/**
 * listenread - get char the client terminal & call fn until char is '\n'
 *@buffer: pointer
 * Return: 1 is successful, -1 if error.
 */
int listenread(char *buffer)
{
	size_t bufsize = SIZEBUFFER;
	size_t c;

	/**fflush(stdin);*/
	c = getline(&buffer, &bufsize, stdin);
	if (c == EOF)
		return (-1);
	return (1);
}
/**
 * _error - allows the error message to be printed in shell
 *
 */
void _error(_track_shell *raw)
{
	printf("/%s: %d: No such file or directory\n", __FILE__, raw->countprocess);
}
/**
 * pid_launch - allows shell to be launched
 *@command: the command needed to pass to the machine to perform
 */
void pid_launch(_track_shell *raw)
{
	pid_t pid;
	char *envp[] = {"", NULL};
	int status;


	if (raw->fullpath != NULL)
	{
		/** create id process (parent & child) to launch command*/
		pid = fork();
		if (pid == 0)
			if (execve(raw->fullpath, raw->argv, envp) == -1)
			{
				_error(raw);
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
	else if (raw->argv[0]='\0')
		_error(raw);
}




