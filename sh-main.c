#include "shell.h"
#include <signal.h>


/**
  * main - Entry to launch program
  * @argc: argument counter
  * @argv: arguments
  * Return: 1.
  */
int main(int argc, char **argv)
{
	/** pointer used to save data input of the terminal client */
	char *line;
	char *argv2[] = {__FILE__, NULL};
	int _isatty;

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
	get_simple_args(argc, argv, line);
	
	/**fseek(stdin, 0, SEEK_END);*/
	fflush(stdin);
	fflush(stdout);
	/** call himself, fn recursive */
	if (_isatty != 0)
		main(1, argv2);
	return (1);
}

void intHandler(int i)
{
	fflush(stdout);
}

