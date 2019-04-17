#include "shell.h"
#include <signal.h>

int printenv(char **);
/**
  * printenv - show vars of enviroment
  * @env: arguments
  * Return: 1.
  */
int printenv(char **env)
{
	int i = 0;

	while (*(env + i) != NULL)
	{
		printf("%s\n", *(env + i));
		i++;
	}
	return (0);
}


/**
  * main - Entry to launch program
  * @argc: argument counter
  * @argv: arguments
  *@env: environment var
  * Return: 1.
  */
int main(int argc, char **argv, char **env __attribute__((unused)))
{
	/** pointer used to save data input of the terminal client */
	char *line;
	/*char *argv2[] = {__FILE__, NULL};*/
	int _isatty;
	int statusbuffer = 0;
	int status_pid = 0;
	char *_ARGS_PATH[] = {"/bin/",
"/sbin/", "/usr/local/sbin/", "/usr/local/bin/",
"/usr/sbin/", "/usr/bin/", "/snap/bin/", NULL};
	/*char **_ARGS_PATH = setpathparams(getpath(env));*/
	signal(SIGINT, intHandler);
	_isatty = isatty(0);
	while (1)
	{
	if (argc == 1)
	{
		line = malloc(sizeof(char) * SIZEBUFFER + 1);
		if (!line)
			exit(100);
		line[SIZEBUFFER] = '\0';
		statusbuffer = listenread(line);
		if (statusbuffer == -1)
		{
			free(line);
			exit(status_pid);
		}
	}
	status_pid = get_simple_args(argc, argv, line, _ARGS_PATH, env);
	if (_isatty != 0)
		prompt();
	fflush(stdin);
	fflush(stdout);
	if (_isatty == 0)
		exit(status_pid);
	}
	return (status_pid);
}
/**
 * intHandler - signal handler
 *@i: variable integer
 */
void intHandler(int i __attribute__((unused)))
{
	write(STDOUT_FILENO, "\n", 1);
	fflush(stdout);
}
/**
 * *getpath - gets the path
 *@env: environment var pointer
 * Return: space
 */
char *getpath(char **env)
{
	char *tmp;

	while (*env != NULL)
	{
		tmp = strtok(*env, "=");
		if (_strcmp(tmp, "PATH") == 0)
		{
			tmp = strtok(NULL, "\0");
			return (tmp);
		}
		env++;
	}
	return ("");
}
/**
 * **setpathparams - sets the path parameters
 *@path: the path of the shell
 * Return: params
 */
char **setpathparams(char *path)
{
	int i = 0;
	char *p;
	int limitparams = 255;
	char **params;

	params = malloc(sizeof(char *) * limitparams);
	if (params == NULL)
		exit(114);
	p = strtok(path, ":");
	params[i] = p;
	while (p != NULL)
	{
		i++;
		p = strtok(NULL, ":");
		params[i] = p;
	}
	return (params);
}
