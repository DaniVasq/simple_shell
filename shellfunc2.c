#include "shell.h"
/**
 * char *_strcat - concatenates two strings.
 * @dest: *dest - destination
 * @src: *src  - source
 *
 * Return: Always 0
 */
char *_strcat(char *dest, char *src)
{
	int i = 0;
	int i2 = 0;

	while (dest[i])
	{
		i++;
	}
	while (src[i2])
	{

		dest[i + i2] = src[i2];
		i2++;
	}
	dest[i + i2] = src[i2];
	return (dest);
}
/**
 * _strlen - returns length of a string.
 *@p: pointer
 * Return: length
 */
long int _strlen(char *p)
{
	long int i = 0;

	while (p[i] != '\0')
		i++;
	return (i);
}
/**
 * args_pop - takes the next value of argument
 *@p: pointer
 * Return: 0 on success, -1 on error
 */
int args_pop(char **p)
{
	int index = 0;

	while (p[index] != NULL)
	{
		p[index] = p[index + 1];
		index++;
	}
	return (0);
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
