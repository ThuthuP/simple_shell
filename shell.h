#ifndef SHELL_H
#define SHELL_H
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 1024
#define MAX_ARGS 20


/* Global environemnt */
extern char **environ;
char *path;
/**/
void fly_drone(void);

void print_prompt(int fd, int is_smile);
void print_string(int fd, const char *str);
void execute_command(char *args[], int *is_smile);
void fly_drone(void);
void exe_command(char *input);
int main(void);
#endif
