#include "shell.h"
#include <signal.h>

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
	while(1)
	{
	if (argc == 1)
	{
		line = malloc(sizeof(char) * SIZEBUFFER + 1);
		if (!line)
			exit(100);
		line[SIZEBUFFER] = '\0';

		/** init the read and write data input of client, it's recursive fn*/
		statusbuffer = listenread(line);
		if (statusbuffer == -1)
		{
			free(line);
			/*free(_ARGS_PATH);*/
			exit (status_pid);
		}
		/*printf("get data line >> %s\n", line);*/
	}	/** parse the pointer to exec the command*/
	status_pid = get_simple_args(argc, argv, line, _ARGS_PATH);
	/** launch prompt */
	if (_isatty != 0)
		prompt();
	/**fseek(stdin, 0, SEEK_END);*/
	fflush(stdin);
	fflush(stdout);
	}
	/** call himself, fn recursive */
	/*if (_isatty != 0 || statusbuffer != -1)
		main(1, argv2, env);*/
	return (status_pid);
}
/**
 * intHandler - signal handler
 *@i: variable integer
 */
void intHandler(int i __attribute__((unused)))
{
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
