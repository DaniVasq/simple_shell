#include "shell.h"
#include <signal.h>

/**
  * main - Entry to launch program
  * @argc: argument counter
  * @argv: arguments
  * Return: 1.
  */
int main(int argc, char **argv, char **env)
{
	/** pointer used to save data input of the terminal client */
	char *line;
	char *argv2[] = {__FILE__, NULL};
	int _isatty;
	char *_PATH = "";
	char **_ARGS_PATH;
	char **_envcopy;

	_envcopy = env;
	_PATH = getpath(env);
	printf("the path is %s\n", _PATH);
	_ARGS_PATH = setpathparams(_PATH);

	while(*_ARGS_PATH != NULL)
	{
		*_ARGS_PATH = strcat(*_ARGS_PATH,"/");
		printf("the params of the path are %s\n", *_ARGS_PATH);
		_ARGS_PATH++;
	}
	*_ARGS_PATH = "/bin/";

	signal(SIGINT, intHandler);
	_isatty = isatty(0);
	if (argc == 1)
	{
		/** launch prompt */
		if (_isatty != 0)
		prompt();
		line = malloc(sizeof(char) * SIZEBUFFER + 1);
		if (!line)
			exit(100);
		line[SIZEBUFFER] = '\0';

		/** init the read and write data input of client, it's recursive fn*/
		if (listenread(line) == -1)
		{
			free(line);
			return (0);
		}
		/*printf("get data line >> %s\n", line);*/
	}

	/** parse the pointer to exec the command*/
	get_simple_args(argc, argv, line, _ARGS_PATH);
	/**fseek(stdin, 0, SEEK_END);*/
	fflush(stdin);
	fflush(stdout);
	/** call himself, fn recursive */
	if (_isatty != 0)
		main(1, argv2, _envcopy);
	return (1);
}

void intHandler(int i)
{
	fflush(stdout);
}

char *getpath(char **env)
{	
	char *tmp;

	while (*env != NULL)
	{
		tmp = strtok(*env, "=");
		if (strcmp(tmp,"PATH") == 0)
		{
			tmp = strtok(NULL, "\0");
			return tmp;
		}
		env++;
	}
	return "";
}

char **setpathparams(char *path)
{
	int i = 0;
	char *p;
	int limitparams = 255;
	char **params;

	params = malloc(sizeof(char *) * limitparams);
	if(params == NULL)
		exit(114);
	p = strtok(path, ":");
	params[i] = p;
	while (p != NULL)
	{
		i++;
		p = strtok(NULL, ":");
		params[i] = p;
	}
	return params;
}
