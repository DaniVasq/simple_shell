#include "shell.h"
#include <signal.h>

void get_isatty(_track_shell *);
void get_terminal(_track_shell *raw);
char find_access(char *, char *);

/**
  * main - Entry to launch program
  * @argc: argument counter
  * @argv: arguments
  * Return: 1.
  */
int main(int argc, char **argv, char **env)
{
	/* struct scalar load containing global args and register attemps*/
	_track_shell *raw = &(struct _raw_data) {1, 0, "interactive", argc, argv, env, (char *)"main", -1, NULL, NULL, 0, NULL};
	
	/*signal(SIGINT, intHandler);*/
	getpath(raw);
	setpathparams(raw);
	get_isatty(raw);
	get_terminal(raw);
	while(raw->keepRunning)
	{
		prompt(raw);
		get_simple_args(raw);
		args_pop(raw);
		update_cmd(raw);
		pid_launch(raw);
		/*free(raw->argv);*/
	}
	/*free(raw->args_path);*/
	fflush(stdin);
	fflush(stdout);
	return (1);
}

void get_terminal(_track_shell *raw)
{
	raw->mode = "interactive";
	if (raw->argc > 1)
		raw->mode = "no-interactive";
	if (raw->argc == 1 && raw->_issatty == 0)
		raw->mode = "workbylote";
}
void get_isatty(_track_shell *raw)
{
	raw->_issatty = isatty(0);
}

void get_simple_args(_track_shell *raw)
{
	char delim[] = " \n";
	char *argx;
	char **options;
	int j = 0, args_max = 255;

	if (strcmp(raw->mode, "interactive") == 0)
        {
		/** pointer used to save data input of the terminal client */
		char *line;

		line = malloc(sizeof(char) * SIZEBUFFER + 1);
		if (!line)
			exit(100);
		line[SIZEBUFFER] = '\0';

		/** init the read and write data input of client, it's recursive fn*/
		/** if listenread == -1 this means that reach the EOF*/
		if (listenread(line) == -1)
		{
			free(line);
			exit(-1);
		}

		if ((int)line[0] == 10)
			free(line);
		else
		{
			options = malloc(sizeof(char *) * args_max + 8);
			if (options == NULL)
			{
				free(options);
				exit(111);
			}
			argx = strtok(line, delim);
			while (argx != NULL)
			{
				options[j] = argx;
				argx = strtok(NULL, delim);
                        	j++;
			}
			options[j] = NULL;
			raw->argc = j;
			raw->argv = options;
			/*free(line);*/
			/*free(options);*/
		}

	}
}

void intHandler(int i)
{
	fflush(stdout);
}

int getpath(_track_shell *raw)
{	
	char *tmp;
	
	while (*raw->env != NULL)
	{
		tmp = strtok(*raw->env, "=");
		if (strcmp(tmp,"PATH") == 0)
		{
			tmp = strtok(NULL, "\0");
			raw->path = tmp;
			return (0);
		}
		raw->env++;
	}
	return (-1);
}

void setpathparams(_track_shell *raw)
{
	int i = 0;
	char *p;
	int limitparams = 255;
	char **params;

	params = malloc(sizeof(char *) * limitparams + 8);
	if(params == NULL)
		exit(114);
	p = strtok(raw->path, ":");
	params[i] = p;
	while (p != NULL)
	{
		i++;
		p = strtok(NULL, ":");
		params[i] = p;
	}
	params[i] = NULL;
	raw->nargs_path = i;
	raw->args_path = params;
}
