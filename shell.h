#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>
#define SIZEBUFFER 1024
typedef struct _raw_data{
        int keepRunning;
        int countprocess;
	char *mode;
        int argc;
        char **argv;
        char **env;
        char *current_fn;
        int _issatty;
        char *path;
        char **args_path;
	int nargs_path;
	char *fullpath;
} _track_shell;


char *_strcat(char *dest, char *src);
void intHandler(int i);
void prompt(_track_shell *);
int listenread(char *);
void get_simple_args(_track_shell *);
void pid_launch(_track_shell *);
void _error(_track_shell *);
long int _strlen(char *);
int args_pop(_track_shell *);
int getpath(_track_shell *);
void setpathparams(_track_shell *);
int update_cmd(_track_shell *);

#endif
