#include "shell.h"

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

/**
 * update_cmd - access to string and updated command
 *@cmd: command
 *@_path: path
 * Return: status (error or no error)
 */
int update_cmd(char **cmd, char **_path)
{

	int index = 0;
	int status = -1;
	char *temp;
	char *temp2;
	struct stat fileStat;

	if (cmd == NULL || _path == NULL)
		exit(110);

	else if (!cmd[index])
		exit(111);
	else
		while (_path[index] != NULL)
		{
			index++;
			temp2 = _path[index];
			temp = _strcat(temp2, cmd[0]);
			if (access(temp, X_OK) == 0)
			{
				cmd[0] = temp;
				status = 1;
				return (status);
			}
		}
	return (status);
}
