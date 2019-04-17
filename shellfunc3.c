#include "shell.h"

/**
* printenv - print env
* @env: pointer contains the list var
* Return: 0
*/
int printenv(char **env)
{
	int i = 0;

	while (*(env + i) != NULL)
	{
		write(STDOUT_FILENO, *(env + i), _strlen(*(env + i)));
		write(STDOUT_FILENO, "\n", _strlen("\n"));
		i++;
	}
	return (0);
}

/**
 * appenddir - appends the "." and "/" of the commands in env path
 *@cmd: command
 * Return: 0 or 1
 */
int appenddir(char *cmd)
{
	int i = 0;

	while (cmd[i] != '\0')
		i++;
	if (i > 2)
	{
		if (cmd[0] == '.' || cmd[0] == '/')
			return (0);
	}
	return (1);
}
