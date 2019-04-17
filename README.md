# Simple Shell

This is a Simple Shell for the Holberton School Simple Shell project. In this project, we use functions, system calls, created processes with fork (child and parent), prototypes, how the shell uses PATH to find programs, and how to execute another program with the execve system call, as well as how to suspend the execution of a process until on its children terminates. We also implement the EOF condition and exit status.

## Getting Started

In this shell project, the following functions were utilized:

|Name |
|:--: |
|_strcpy |
|_strlen |
|_strcmp |
|intHandler |
|*getpath |
|_getline |
|**setpathparams |
|*str_concat |
|*get_value_env |
|_strcmp |
|*_strcat |
|prompt |
|listenread |
|main |
|get_simple_args |
|pid_launch |
|_error |
|_strlen |
|args_pop |
|*getpath |
|**setpathparams |
|update_cmd |
|appenddir |

## Making use of the Shell:

In order to pull up the shell, you'll need to follow these instructions:
1. Clone this repo: https://github.com/DaniVasq/simple_shell
2. Go to the directory simple_shell/ by typing in cd simple_shell
2. Compile with: gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
3. Execute with: ./hsh
4. Make use of the shell by typing in commands with the path. Example: type in /bin/ls or /bin/ls/ -l, or /bin/pwd. This will list the files in the current directory, list files in long format, and list the current working directory, respectively.

In order to make use of the Shell in non-interactive mode, you can type in echo "/bin/ls" | ./hsh, this will pass the command from standard output to standard input.

## Files
Our c program and header files are organized and separated to include five or less functions per file. These are their names:
1. 3-strcmp.c
2. sh-main.c
3. shell.h
4. shellfunc1.c
5. shellfunc2.c
6. shellfunc3.c

## Extras
We have also included a README.md file, an AUTHORS file, and a manpage (man_1_simple_shell) file.

# Authors
Laura Vasquez, Fesus Rocuts