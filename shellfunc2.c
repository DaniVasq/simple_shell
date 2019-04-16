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
 * char _strelen - returns length of a string.
 *
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
 *
 * Return: 0 on success, -1 on error
 */
int args_pop(_track_shell *raw)
{
	int index = 0;

	if (strcmp(raw->mode, "no-interactive") == 0)
	{
		while (raw->argv[index] != NULL)
		{
			raw->argv[index] = raw->argv[index+1];
			index++;
		}
		raw->mode = "interactive";
	}
	return (0);
}

/**
 * update_cmd - access to string and updated command
 *
 * Return: status (error or no error)
 */
int update_cmd(_track_shell *raw)
{
	int index = 0;
	int status = -1;
	char *dir = NULL;
	char *file = NULL;
	char *fullpath = NULL;

	if (raw->argv[0] == NULL || raw->path == NULL)
		exit(110);
	else if (!raw->argv[index])
		exit(111);
	else
	{	
		dir = strdup(*(raw->args_path + index));
		raw->fullpath = NULL;
		while(index < raw->nargs_path)
		{
			dir = strdup(*(raw->args_path + index));
			file = strdup(raw->argv[0]);
			fullpath = strcat(dir, "/");
			fullpath = strcat(fullpath, file);
			/*printf("find dir= %s,file= %s, fullpath=%s\n", dir, file, fullpath);*/
			if (access(fullpath, X_OK) == 0)
			{
				/*printf("the params of the path are %s\n", fullpath);*/
				raw->fullpath = fullpath;
				status = 1;
				return (status);
			}
			index++;
		}
		free(dir);
		free(file);
	}
	return (status);
}
