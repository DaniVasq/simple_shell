# simple_shell
Simple Shell for Holberton School project.

This command contains this code
1 |#!/bin/bash
2 |SHELL='./shell'
3 |echo exit | $SHELL | wc -l | awk '{ if($1 == 0) print "ok"; else print "ko"}'

Explanation:

The first line is the shebang,
The next line has a variable that indicate the file shell
The last line has the bash script that allow validate the command exit of your shell, if is correct this print 'ok' otherwise print 'ko'
