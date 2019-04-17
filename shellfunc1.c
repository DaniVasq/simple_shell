#include "shell.h"
/**
 * prompt - function for the print symbol before the user types
 *
 * Return: nothing.
 */
void prompt(void)
{
	/** symbol > */
	/*putchar(62);*/
	/** symbol space */
	/*putchar(32);*/
}
/**
 * listenread - get char the client terminal & call fn until char is '\n'
 *@buffer: pointer
 * Return: 1 is successful, -1 if error.
 */
int listenread(char *buffer)
{
	size_t bufsize = SIZEBUFFER;
	ssize_t c;

	/**fflush(stdin);*/
	c = getline(&buffer, &bufsize, stdin);
	if (c == EOF)
		return (-1);
	else if (_strcmp(buffer, "exit") == 10)
		return (-1);
	return (1);
}
/**
 * get_simple_args - this fn splits the string when space char is found
 *@argc: argument counter
 *@argv: where the arguments are contained
 *@args: arguments
 *@_path: path
 */
void get_simple_args(int argc, char **argv, char *args, char **_path)
{
	char delim[] = " \n";
	char **options;
	char *argx;
	int j = 0;
	int args_max = 255;
	(void)_path;

	if (argc == 1)
	{
		if ((int)args[0] == 10)
			free(args);
		else
		{
			options = malloc(sizeof(char *) * args_max);
			if (options == NULL)
			{
				free(options);
				exit(111);
			}
			argx = strtok(args, delim);
			while (argx != NULL)
			{
				options[j] = argx;
				argx = strtok(NULL, delim);
				j++;
			}
			options[j] = NULL;
			/*if (update_cmd(options, _path))*/
			if (options[0] != NULL && _strlen(options[0]) > 0)
				pid_launch(options, args, _path);
			free(args);
			free(options);
		}
	}
	else if (argc >= 2)
	{
		args_pop(argv);
		/*update_cmd(argv, _path);*/
		pid_launch(argv, NULL, NULL);
	}
}

/**
 * _error - allows the error message to be printed in shell
 *
 */
void _error(void)
{
	printf("/%s: No such file or directory\n", __FILE__);
}
/**
 * pid_launch - make a fork to create child process who execute the command
 *@args: arguments
 *@_path: path
 *@pid_launch: launches the process
 *@_argv: argument container
 */
int pid_launch(char **_argv, char *args, char **_path)
{
	pid_t pid;
	char *envp[] = {"", NULL}, *dir = NULL, *file = NULL, *fullpath = NULL;
	int status, j = 0, searchpath = 1, accessfile = 0;
	struct stat fileStat;

	pid = fork();
	if (pid == 0)
	{
		file =  _argv[0];
		while (*(_path + j) != NULL && searchpath == 1)
		{searchpath = appenddir(file);
			dir = str_concat(NULL, *(_path + j));
			/*dir = strdup(*(_path + j));*/
			fullpath = searchpath == 1 ? str_concat(dir, file) : file;
			if (stat(fullpath, &fileStat) == 0)
			{accessfile = 1;
				searchpath = 0; }
			j++;
			free(dir); }
		if (accessfile)
		{
			if (execve(fullpath, _argv, envp) == -1)
			{_error();
				free(args);
				free(_argv);
				exit(-1); }
		}
		else
		{free(args);
			free(_argv);
			_error();
			exit(2); }
	}
	else if (pid < 0)
	{free(args);
		free(_path);
		free(_argv);
		exit(102); }
	else
		waitpid(pid, &status, 0);
	return (WIFEXITED(status) & 255);
}
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
