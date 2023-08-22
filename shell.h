#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#define MAX_BUFFER_SIZE 1024
int find_command(const char *command, char *full_path, size_t buffer_size);
void print_string(int fd, const char *str);
void prompt_user(void);

#endif /* SHELL_H */

