#include "shell.h"

/**
 *str_concat - Duplicate string
 *@s1: string one
 *@s2: string two
 * Return: pointer to copy array
 */
char *str_concat(char *s1, char *s2)
{
	char *p;
	unsigned int i;
	unsigned int size_s1, size_s2;

	if (s1 == NULL)
		s1 = "";
	if (s2 == NULL)
		s2 = "";
	for (size_s1 = 0; *(s1 + size_s1) && s1; size_s1++)
	{
	}
	for (size_s2 = 0; *(s2 + size_s2) && s2; size_s2++)
	{
	}
	p =  malloc(sizeof(char) * (size_s1 + size_s2 + 1));
	if (p == NULL)
		return (NULL);
	for (i = 0; i < size_s1 + size_s2; i++)
	{
		if (i < size_s1)
			p[i] = *(s1 + i);
		else
			p[i] = *(s2 + i - size_s1);
	}
	p[i] = '\0';
	return (p);
}

/**
 *get_value_env - find the value of enviroment variable
 *@envp: enviroment variables
 *@variable: variable to search
 *Return: pointer start on value of variable
 */
char *get_value_env(char **envp, char *variable)
{
	unsigned int envp_i = 0, variable_i = 0;
	char flag;

	while (envp[envp_i])
	{
		flag = 1;
		while (variable[variable_i] && flag)
		{
			if (envp[envp_i][variable_i] != variable[variable_i])
				flag = 0;
			variable_i++;
		}
		if (flag)
		{
			return (&envp[envp_i][variable_i + 1]);
		}
		variable_i = 0;
		envp_i++;
	}
	return (NULL);
}

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
