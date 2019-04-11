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
int args_pop(char ***p)
{
	int index;
	if (!p)
		return (-1);
	while (p[index] != '\0')
		p[index] = p[index++];
	return (0);
}
