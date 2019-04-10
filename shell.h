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
void intHandler(int i);
void prompt(void);
long int listenread(char *);
void get_simple_args(int, char **, char *);
void pid_launch(char *);
void _error(void);
long int _strlen(char *);
#endif
