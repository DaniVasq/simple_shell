/**
 * prompt - function for the print symbol before the user types
 *
 * Return: nothing.
 */
void prompt(void)
{
	/** symbol > */
	putchar(62);
	/** symbol space */
	putchar(32);
}
/**
 * listenread - get char the client terminal & call fn until char is '\n'
 *@buffer: pointer
 * Return: 1 is successful, -1 if error.
 */
int listenread(char *buffer)
{
	size_t bufsize = SIZEBUFFER;
	size_t c;

	/**fflush(stdin);*/
	c = getline(&buffer, &bufsize, stdin);
	if (!c)
		return (-1);
	return (1);
}
/**
 * get_simple_args - this fn splita the string when space char is found
 *@argc: argument counter
 *@argv: where the arguments are contained
 *@args: arguments
 */
void get_simple_args(int argc, char **argv __attribute__((unused)), char *args __attribute__((unused)))
{
	char delim[] = " \n";
	char *command;
	int exists_space = 0;
	int i = 0, t = 0;

	if (argc == 1 && strlen(args) > 1)
	{
		while (args[i] != '\0')
		{
			if (args[i] == ' ')
				exists_space++;
			/**if (args[i] == EOF)
				free(args);
			exit(0);*/
			i++;
		}
		command = (char *)strtok(args, delim);
		if (exists_space > 0)
			_error();
		else if (i > 0 && command != NULL)
			pid_launch((char *)command);
		free(args);
	}
	else if (argc == 2)
		pid_launch(argv[1]);
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
 * pid_launch - allows shell to be launched
 *@command: the command needed to pass to the machine to perform
 */
void pid_launch(char *command)
{
	pid_t pid;
	char *envp[] = {"", NULL};
	/*char *envp[] = {"/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin",NULL};*/
	int status;
	char *_argv[] = {command, NULL};

	if (strlen(command) > 0)
	{
		/** create id process (parent & child) to launch command*/
		pid = fork();
		if (pid == 0)
			if (execve(command, _argv, envp) == -1)
			{
				_error();
				exit(103);
			}
		else if (pid < 0)
		{
			exit(102);
		}
		/** always wait the pid is kill*/
		do {
			waitpid(pid, &status, 0);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}
}
