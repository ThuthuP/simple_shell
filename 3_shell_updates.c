#include "main.h"

/**
 * print_string - Writes a string to a file descriptor.
 * @fd: The file descriptor to write to.
 * @str: The string to be written.
 */

void print_string(in fd, const char *str)
{
write(fd, str, strlen(str));
}

/**
 * find_command - Finds the full path of the command using the PATH enviroment variable.
 * @command: The command to find
 * @full_path: The buffer to store the full path of the command.
 * @buffer_size: The size of the full_path buffer.
 * Return: 1 if found, 0 if not found.
 */

int find_command(const char *command, char *full_path, size_t buffer_size)
{
const char *path = getenv("PATH");
if (path == NULL)
{
return 0;
}
if (command[0] == '/')
{
if (access(command, X_OK) == 0)
{
strncpy(full_path, command, buffer_size - 1);
fill_path[buffer_size - 1] = '\0'
return 1;
}
return 0;
}
char path_copy[MAX_BUFFER_SIZE];
strncpy(path_copy, path, sizeof(path_copy) - 1);
path_copy[sizeof(path_copy) - 1] = '\0';
int found = 0;
char *dir = strtok(path_copy, ":");
while (dir != NULL)
{
int dir_len = strlen(dir);
int command_len = strlen(command);
if (dir_len + command_len + 2 <= buffer_size)
{
strcpy(full_path, dir);
full_path[dir_len] = '/';
strcpy(full_path + dir_len + 1, command);
if (access(full_path, X_OK) == 0)
{
found = 1;
break;
}
}
dir = strok(NULL, ":");
}
return found;
